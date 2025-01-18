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

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		LuaExecutor::GetInstance()->OnInitialize([](lua_State* L) {
			if (luaL_dostring(L, "unsafe_env.sm.keyapi_injected = true") != LUA_OK) {
				INFO("Failed to create unsafe_env.sm!");
				return;
			}

			lua_getglobal(L, "unsafe_env");
			lua_getfield(L, -1, "sm");
			lua_pushcclosure(L, keyapi_getkeystate, 0);
			lua_setfield(L, -2, "getKeyState");
			lua_pop(L, 2);

			INFO("Injected SM-KeyAPI into Lua environment!");
			}, true);

		INFO("SM-KeyAPI loaded!");
	}

	if (dwReason == DLL_PROCESS_DETACH) {
		INFO("SM-KeyAPI unloaded!");
	}

	return TRUE;
}
