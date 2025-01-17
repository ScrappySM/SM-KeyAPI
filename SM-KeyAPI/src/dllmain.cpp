/// How this mod works:
/// - We hook the loadLuaEnv function, which is called when the game loads the Lua environment.
/// - We inject a function into the Lua environment that allows us to check the state of a key (implemented in C++ as `keyapi_getkeystate`).
///
/// - In the `keyapi_getkeystate` function, we check if the ScrapMechanic window is the active window.
/// - If it is, we check the state of the key and return it to the Lua environment.
///
/// How to update the mod (assumes IDA):
/// - Go the to names subview (Shift + F4)
/// - Search for `luaopen_base`
/// - XRef to the function
/// - The function you arrive at is the loadLuaEnv function, update the offset in `include/sm/offsets.h`

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <optional>

#include <polyhook2/Detour/NatDetour.hpp>
#include <polyhook2/IHook.hpp>

#include <sm/offsets.h>

#include <carbon/lua/lua.hpp>
#include <carbon/contraption.h>
#include <carbon/tools.h>

#include "utils.h"

static int keyapi_getkeystate(lua_State* L) {
	// Check that ScrapMechanic is the active window, we don't want any keyloggers made using SM...
	if (GetForegroundWindow() != FindWindowA("CONTRAPTION_WINDOWS_CLASS", nullptr)) {
		lua_pushinteger(L, 0);
		return 1;
	}

	const char* key = luaL_checklstring(L, 1, nullptr);
	lua_pushinteger(L, (int)getKeyState(std::string(key)));

	return 1;
}

static std::optional<PLH::NatDetour> detour = std::nullopt;
static uint64_t hkLoadLuaEnvTramp = NULL;
// __int64 __fastcall loadLuaEnv(__int64 *luaVM, _QWORD **loadFuncs, int envFlag)
NOINLINE uint64_t __cdecl hkLoadLuaEnv(uint64_t* luaVM, uint64_t** loadFuncs, int envFlag) {
	auto oRes = PLH::FnCast(hkLoadLuaEnvTramp, &hkLoadLuaEnv)(luaVM, loadFuncs, envFlag);
	lua_State* L = reinterpret_cast<lua_State*>(*luaVM);

	INFO("Injecting keyapi into Lua environment...");

	if (!oRes && L) {
		if (luaL_dostring(L, "unsafe_env.sm.keyapi_injected = true") != 0) {
			std::cout << "Failed to inject keyapi into Lua environment!" << std::endl;
			return oRes;
		}

		lua_getglobal(L, "unsafe_env");
		lua_getfield(L, -1, "sm");
		lua_pushcclosure(L, keyapi_getkeystate, 0);
		lua_setfield(L, -2, "getKeyState");
	}

	return oRes;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		std::cout << "DLL_PROCESS_ATTACH" << std::endl;

		auto contraption = Carbon::SM::Contraption::GetInstance();
		while (!contraption || contraption->gameState <= Carbon::SM::GameStateType::Null || contraption->gameState >= Carbon::SM::GameStateType::WorldBuilder || contraption->gameState == Carbon::SM::GameStateType::Load) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			contraption = Carbon::SM::Contraption::GetInstance();
		}

		detour.emplace((uint64_t)SM::Offsets::Rebased::loadLuaEnv, (uint64_t)&hkLoadLuaEnv, &hkLoadLuaEnvTramp);
		detour.value().hook();

		INFO("KeyAPI injected into Lua environment!");
	}

	if (dwReason == DLL_PROCESS_DETACH) {
		std::cout << "DLL_PROCESS_DETACH" << std::endl;

		detour.value().unHook();
		INFO("KeyAPI removed from Lua environment!");
	}

	return TRUE;
}
