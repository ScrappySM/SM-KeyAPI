#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory>
#include <optional>
#include <string>
#include <cstdarg>
#include <stddef.h>
#include <cstdint>
#include <queue>
#include <functional>

#include <polyhook2/Detour/NatDetour.hpp>
#include <polyhook2/IHook.hpp>

#include "carbon/lua/lua.hpp"
#include "carbon/utils.h"
#include "carbon/tools.h"
#include "carbon/offsets.h"
#include "carbon/contraption.h"


struct LuaVM {
	/* 0x0000 */ PUB lua_State* L;
};

// LuaManager::GetInstance()->luaVM->L
struct LuaManager {
	SINGLETON(LuaManager);

	/* 0x0000 */ PAD(0x2E8);
	/* 0x02E8 */ PUB std::shared_ptr<LuaVM> luaVM;
};

class LuaExecutor {
public:
	LuaExecutor() {
		using namespace Carbon::Offsets::Rebased;
		this->updateDetour.emplace((uint64_t)UpdateFunc, (uint64_t)&hkUpdateFunction, &hkUpdateFunctionTramp);
		this->initDetour.emplace((uint64_t)LoadLuaEnvFunc, (uint64_t)&hkLoadLuaEnvFunc, &hkLoadLuaEnvFuncTramp);
		this->updateDetour->hook();
		this->initDetour->hook();
	}

	~LuaExecutor() {
		this->updateDetour->unHook();
		this->initDetour->unHook();
		this->updateDetour.reset();
		this->initDetour.reset();
	}

	LuaExecutor(const LuaExecutor&) = delete;
	LuaExecutor& operator=(const LuaExecutor&) = delete;

	static LuaExecutor* GetInstance() {
		static LuaExecutor instance;
		return &instance;
	}

	/// <summary>
	/// Queues a function to be called when the Lua VM is updated.
	/// </summary>
	/// <param name="func">The function to call.</param>
	void OnUpdate(std::function<void(lua_State*)> func, bool removeAfterExecution = false) {
		this->updateFuncs.push({ func, removeAfterExecution });
	}

	/// <summary>
	/// Queues a function to be called when the Lua VM is initialized.
	/// These functions are never cleared from the queue, they are called every time the Lua VM is initialized.
	/// </summary>
	/// <param name="func">The function to call.</param>
	/// <param name="immediateIfPlaying">Whether to also call the function immediately if the game is already playing.</param>
	void OnInitialize(std::function<void(lua_State*)> func, bool immediateIfPlaying = true) {
		this->initFuncs.push_back(func);

		if (immediateIfPlaying && Carbon::SM::Contraption::IsPlaying()) {
			INFO("Game is already playing, calling supposed init function immediately");
			this->updateFuncs.emplace(func, true); // Only call once
		}
	}

private:
	void Update(lua_State* L) {
		while (!this->updateFuncs.empty()) {
			auto& [func, remove] = this->updateFuncs.front();
			func(L);
			if (remove) this->updateFuncs.pop();
		}
	}

	static inline uint64_t hkUpdateFunctionTramp = NULL;
	static __declspec(noinline) uint64_t __cdecl hkUpdateFunction(__int64 a1, __int64 a2, __int64 a3) {
		auto oRes = PLH::FnCast(hkUpdateFunctionTramp, &hkUpdateFunction)(a1, a2, a3);

		// These checks are rather novel since by the time the update function is called, the Lua VM should have been initialized
		// and the LuaManager should have been created. However, it's better to be safe than sorry.
		auto& luaVM = LuaManager::GetInstance()->luaVM;
		if (luaVM) {
			auto L = luaVM->L;
			if (L) {
				auto executor = LuaExecutor::GetInstance();
				executor->Update(L);
			}
		}

		return oRes;
	}

	static inline uint64_t hkLoadLuaEnvFuncTramp = NULL;
	static __declspec(noinline) uint64_t __cdecl hkLoadLuaEnvFunc(uint64_t* luaVM, uint64_t** loadFuncs, int envFlag) {
		auto oRes = PLH::FnCast(hkLoadLuaEnvFuncTramp, &hkLoadLuaEnvFunc)(luaVM, loadFuncs, envFlag);
		INFO("LoadLuaEnv({}, {}, {})", (void*)luaVM, (void*)loadFuncs, envFlag);

		auto& luaVMPtr = LuaManager::GetInstance()->luaVM;
		if (!luaVMPtr) return oRes;

		auto L = luaVMPtr->L;
		if (!L) return oRes;

		auto executor = LuaExecutor::GetInstance();
		for (auto& func : executor->initFuncs) {
			func(L);
		}

		return oRes;
	}

	std::optional<PLH::NatDetour> updateDetour = std::nullopt;
	std::optional<PLH::NatDetour> initDetour = std::nullopt;

	std::queue<std::pair<std::function<void(lua_State*)>, bool>> updateFuncs;
	std::vector<std::function<void(lua_State*)>> initFuncs;
};
