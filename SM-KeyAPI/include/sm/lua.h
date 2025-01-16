#pragma once

#include <string>

struct lua_State; // Forward declaration, the game knows the real definition
struct lua_CFunction; // Forward declaration, the game knows the real definition

typedef void(__cdecl* lua_pushcclosure_t)(lua_State*, lua_CFunction*, int);
typedef void(__cdecl* lua_modfield_t)(lua_State*, int, const char*);
typedef void(__cdecl* lua_getglobal_t)(lua_State*, const char*);
typedef void(__cdecl* lua_pushboolean_t)(lua_State*, int);
typedef int(__cdecl* lua_modinteger_t)(lua_State*, int);
typedef int(__cdecl* luaL_loadstring_t)(lua_State*, const char*);
typedef int(__cdecl* lua_pcall_t)(lua_State*, int, int, int);
typedef const char* (__cdecl* luaL_checklstring_t)(lua_State*, int, size_t*);
typedef void(__cdecl* lua_pushinteger_t)(lua_State*, int);

static constexpr int LUA_GLOBALSINDEX = -10002;
#define lua_getglobal(L,s) lua_getfield(L, LUA_GLOBALSINDEX, s)

template <typename T>
T GetLuaFunction(const std::string& name) {
	static HMODULE hLuaDLL = GetModuleHandleA("lua51.dll");
	if (!hLuaDLL) {
		std::cout << "lua51.dll not found!" << std::endl;
		return nullptr;
	}
	return (T)GetProcAddress(hLuaDLL, name.c_str());
}

static auto luaL_loadstring = GetLuaFunction<luaL_loadstring_t>("luaL_loadstring");
static auto lua_pcall = GetLuaFunction<lua_pcall_t>("lua_pcall");
static auto lua_pushcclosure = GetLuaFunction<lua_pushcclosure_t>("lua_pushcclosure");
static auto lua_setfield = GetLuaFunction<lua_modfield_t>("lua_setfield");
static auto lua_getfield = GetLuaFunction<lua_modfield_t>("lua_getfield");
static auto lua_pushboolean = GetLuaFunction<lua_pushboolean_t>("lua_pushboolean");
static auto lua_tointeger = GetLuaFunction<lua_modinteger_t>("lua_tointeger");
static auto lua_pushinteger = GetLuaFunction<lua_modinteger_t>("lua_pushinteger");
static auto luaL_checklstring = GetLuaFunction<luaL_checklstring_t>("luaL_checklstring");

bool hasAllLuaFunctions() {
#define CHECK_LUA_FUNC(func) if (!func) { std::cout << #func << " not found!" << std::endl; failed = true; }
	bool failed = false;
	CHECK_LUA_FUNC(luaL_loadstring);
	CHECK_LUA_FUNC(lua_pcall);
	CHECK_LUA_FUNC(lua_pushcclosure);
	CHECK_LUA_FUNC(lua_setfield);
	CHECK_LUA_FUNC(lua_getfield);
	CHECK_LUA_FUNC(lua_pushboolean);
	CHECK_LUA_FUNC(lua_tointeger);
	CHECK_LUA_FUNC(lua_pushinteger);
	CHECK_LUA_FUNC(luaL_checklstring);
#undef CHECK_LUA_FUNC
	return !failed;
}
