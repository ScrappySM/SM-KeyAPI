#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <optional>

#include <polyhook2/Detour/NatDetour.hpp>
#include <polyhook2/IHook.hpp>

#include <sm/offsets.h>
#include <sm/lua.h>

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

	if (!hasAllLuaFunctions())
		return oRes;

	if (!oRes && L) {
		const int loadRes = luaL_loadstring(L, "unsafe_env.sm.keyapi_injected = true");
		if (!loadRes)
			lua_pcall(L, 0, 0, 0);

		lua_getglobal(L, "unsafe_env");
		lua_getfield(L, -1, "sm");
		lua_pushcclosure(L, (lua_CFunction*)keyapi_getkeystate, 0);
		lua_setfield(L, -2, "getKeyState");

		return loadRes;
	}

	return oRes;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		std::cout << "DLL_PROCESS_ATTACH" << std::endl;

		detour.emplace((uint64_t)SM::Offsets::Rebased::loadLuaEnv, (uint64_t)&hkLoadLuaEnv, &hkLoadLuaEnvTramp);
		detour.value().hook();
		std::cout << "loadLuaEnv " << std::hex << (uint64_t)SM::Offsets::Rebased::loadLuaEnv << " hooked!" << std::endl;
	}

	if (dwReason == DLL_PROCESS_DETACH) {
		std::cout << "DLL_PROCESS_DETACH" << std::endl;

		detour.value().unHook();
		std::cout << "loadLuaEnv " << std::hex << (uint64_t)SM::Offsets::Rebased::loadLuaEnv << " unhooked!" << std::endl;
	}

	return TRUE;
}
