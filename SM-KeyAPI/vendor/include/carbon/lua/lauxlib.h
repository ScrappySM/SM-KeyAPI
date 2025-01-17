#pragma once

#include <stddef.h>
#include <stdio.h>

#include "lua.h"

#define LUAL_BUFFERSIZE   ((int)(16 * sizeof(void*) * sizeof(lua_Number)))

typedef struct luaL_Buffer {
  char *p;			/* current position in buffer */
  int lvl;  /* number of strings in the stack (level) */
  lua_State *L;
  char buffer[LUAL_BUFFERSIZE];
} luaL_Buffer;

#define luaL_getn(L,i)          ((int)lua_objlen(L, i))
#define luaL_setn(L,i,j)        ((void)0)  /* no op! */

#define LUA_ERRFILE     (LUA_ERRERR+1)

#define LUA_NOREF       (-2)
#define LUA_REFNIL      (-1)

typedef struct luaL_Reg {
  const char *name;
  lua_CFunction func;
} luaL_Reg;

namespace Carbon::Lua::Prototypes {
	typedef void (luaI_openlib_t)(lua_State* L, const char* libname,
		const luaL_Reg* l, int nup);
	typedef void (luaL_register_t)(lua_State* L, const char* libname,
		const luaL_Reg* l);
	typedef int (luaL_getmetafield_t)(lua_State* L, int obj, const char* e);
	typedef int (luaL_callmeta_t)(lua_State* L, int obj, const char* e);
	typedef int (luaL_typerror_t)(lua_State* L, int narg, const char* tname);
	typedef int (luaL_argerror_t)(lua_State* L, int numarg, const char* extramsg);
	typedef const char* (luaL_checklstring_t)(lua_State* L, int numArg,
		size_t* l);
	typedef const char* (luaL_optlstring_t)(lua_State* L, int numArg,
		const char* def, size_t* l);
	typedef lua_Number(luaL_checknumber_t) (lua_State* L, int numArg);
	typedef lua_Number(luaL_optnumber_t) (lua_State* L, int nArg, lua_Number def);

	typedef lua_Integer(luaL_checkinteger_t) (lua_State* L, int numArg);
	typedef lua_Integer(luaL_optinteger_t) (lua_State* L, int nArg,
		lua_Integer def);

	typedef void (luaL_checkstack_t)(lua_State* L, int sz, const char* msg);
	typedef void (luaL_checktype_t)(lua_State* L, int narg, int t);
	typedef void (luaL_checkany_t)(lua_State* L, int narg);

	typedef int   (luaL_newmetatable_t)(lua_State* L, const char* tname);
	typedef void* (luaL_checkudata_t)(lua_State* L, int ud, const char* tname);

	typedef void (luaL_where_t)(lua_State* L, int lvl);
	typedef int (luaL_error_t)(lua_State* L, const char* fmt, ...);

	typedef int (luaL_checkoption_t)(lua_State* L, int narg, const char* def,
		const char* const lst[]);

	typedef int (luaL_ref_t)(lua_State* L, int t);
	typedef void (luaL_unref_t)(lua_State* L, int t, int ref);

	typedef int (luaL_loadfile_t)(lua_State* L, const char* filename);
	typedef int (luaL_loadbuffer_t)(lua_State* L, const char* buff, size_t sz,
		const char* name);
	typedef int (luaL_loadstring_t)(lua_State* L, const char* s);

	typedef lua_State* (luaL_newstate_t)(void);

	typedef const char* (luaL_gsub_t)(lua_State* L, const char* s, const char* p,
		const char* r);

	typedef const char* (luaL_findtable_t)(lua_State* L, int idx,
		const char* fname, int szhint);

	typedef void (luaL_buffinit_t)(lua_State* L, luaL_Buffer* B);
	typedef char* (luaL_prepbuffer_t)(luaL_Buffer* B);
	typedef void (luaL_addlstring_t)(luaL_Buffer* B, const char* s, size_t l);
	typedef void (luaL_addstring_t)(luaL_Buffer* B, const char* s);
	typedef void (luaL_addvalue_t)(luaL_Buffer* B);
	typedef void (luaL_pushresult_t)(luaL_Buffer* B);
} // namespace Carbon::Lua::Prototypes

/// <summary>
/// Opens a library.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="libname">The library name.</param>
/// <param name="l">The library.</param>
/// <param name="nup">The number of upvalues.</param>
/// <returns></returns>
inline void luaI_openlib(lua_State* L, const char* libname,
	const luaL_Reg* l, int nup) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaI_openlib_t>("luaI_openlib")(L, libname, l, nup);
}

/// <summary>
/// Registers a library.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="libname">The library name.</param>
/// <param name="l">The library.</param>
/// <returns></returns>
inline void luaL_register(lua_State* L, const char* libname,
	const luaL_Reg* l) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_register_t>("luaL_register")(L, libname, l);
}

/// <summary>
/// Gets the metafield of the object.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="obj">The object.</param>
/// <param name="e">The field.</param>
/// <returns></returns>
inline int luaL_getmetafield(lua_State* L, int obj, const char* e) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_getmetafield_t>("luaL_getmetafield")(L, obj, e);
}

/// <summary>
/// Calls the metafield of the object.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="obj">The object.</param>
/// <param name="e">The field.</param>
/// <returns></returns>
inline int luaL_callmeta(lua_State* L, int obj, const char* e) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_callmeta_t>("luaL_callmeta")(L, obj, e);
}

/// <summary>
/// Checks the type error.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="narg">The argument.</param>
/// <param name="tname">The type name.</param>
/// <returns></returns>
inline int luaL_typerror(lua_State* L, int narg, const char* tname) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_typerror_t>("luaL_typerror")(L, narg, tname);
}

/// <summary>
/// Checks the argument error.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="numarg">The argument number.</param>
/// <param name="extramsg">The extra message.</param>
/// <returns></returns>
inline int luaL_argerror(lua_State* L, int numarg, const char* extramsg) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_argerror_t>("luaL_argerror")(L, numarg, extramsg);
}

/// <summary>
/// Checks the string.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="numArg">The argument number.</param>
/// <param name="l">The length.</param>
/// <returns>The string.</returns>
inline const char* luaL_checklstring(lua_State* L, int numArg, size_t* l) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checklstring_t>("luaL_checklstring")(L, numArg, l);
}

/// <summary>
/// Checks the optional string.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="numArg">The argument number.</param>
/// <param name="def">The default value.</param>
/// <param name="l">The length.</param>
/// <returns>The string.</returns>
inline const char* luaL_optlstring(lua_State* L, int numArg, const char* def, size_t* l) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_optlstring_t>("luaL_optlstring")(L, numArg, def, l);
}

/// <summary>
/// Checks the number.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="numArg">The argument number.</param>
/// <returns>The number.</returns>
inline lua_Number luaL_checknumber(lua_State* L, int numArg) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checknumber_t>("luaL_checknumber")(L, numArg);
}

/// <summary>
/// Checks the optional number.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="nArg">The argument number.</param>
/// <param name="def">The default value.</param>
/// <returns>The number.</returns>
inline lua_Number luaL_optnumber(lua_State* L, int nArg, lua_Number def) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_optnumber_t>("luaL_optnumber")(L, nArg, def);
}

/// <summary>
/// Checks the integer.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="numArg">The argument number.</param>
/// <returns>The integer.</returns>
inline lua_Integer luaL_checkinteger(lua_State* L, int numArg) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checkinteger_t>("luaL_checkinteger")(L, numArg);
}

/// <summary>
/// Checks the optional integer.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="nArg">The argument number.</param>
/// <param name="def">The default value.</param>
/// <returns>The integer.</returns>
/// <returns></returns>
inline lua_Integer luaL_optinteger(lua_State* L, int nArg, lua_Integer def) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_optinteger_t>("luaL_optinteger")(L, nArg, def);
}

/// <summary>
/// Checks the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="sz">The size.</param>
/// <param name="msg">The message.</param>
/// <returns></returns>
inline void luaL_checkstack(lua_State* L, int sz, const char* msg) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checkstack_t>("luaL_checkstack")(L, sz, msg);
}

/// <summary>
/// Checks the type.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="narg">The argument.</param>
/// <param name="t">The type.</param>
/// <returns></returns>
inline void luaL_checktype(lua_State* L, int narg, int t) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checktype_t>("luaL_checktype")(L, narg, t);
}

/// <summary>
/// Checks any.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="narg">The argument.</param>
/// <returns></returns>
inline void luaL_checkany(lua_State* L, int narg) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checkany_t>("luaL_checkany")(L, narg);
}

/// <summary>
/// Creates a new metatable.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="tname">The type name.</param>
/// <returns></returns>
inline int luaL_newmetatable(lua_State* L, const char* tname) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_newmetatable_t>("luaL_newmetatable")(L, tname);
}

/// <summary>
/// Checks the user data.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="ud">The user data.</param>
/// <param name="tname">The type name.</param>
/// <returns>The user data.</returns>
inline void* luaL_checkudata(lua_State* L, int ud, const char* tname) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checkudata_t>("luaL_checkudata")(L, ud, tname);
}

/// <summary>
/// Wheres the function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="lvl">The level.</param>
/// <returns></returns>
inline void luaL_where(lua_State* L, int lvl) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_where_t>("luaL_where")(L, lvl);
}

/// <summary>
/// Checks the error.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="fmt">The format.</param>
/// <returns></returns>
inline int luaL_error(lua_State* L, const char* fmt, ...) {
	using namespace Carbon::Lua::Prototypes;
	va_list args;
	va_start(args, fmt);
	int result = GetFunc<luaL_error_t>("luaL_error")(L, fmt, args);
	va_end(args);
	return result;
}

/// <summary>
/// Checks the option.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="narg">The argument.</param>
/// <param name="def">The default.</param>
/// <param name="lst">The list.</param>
/// <returns></returns>
inline int luaL_checkoption(lua_State* L, int narg, const char* def,
	const char* const lst[]) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_checkoption_t>("luaL_checkoption")(L, narg, def, lst);
}

/// <summary>
/// Creates a reference.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="t">The table.</param>
/// <returns>The reference.</returns>
inline int luaL_ref(lua_State* L, int t) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_ref_t>("luaL_ref")(L, t);
}

/// <summary>
/// Unreferences.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="t">The table.</param>
/// <param name="ref">The reference.</param>
/// <returns></returns>
inline void luaL_unref(lua_State* L, int t, int ref) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_unref_t>("luaL_unref")(L, t, ref);
}

/// <summary>
/// Loads a file.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="filename">The filename.</param>
/// <returns></returns>
inline int luaL_loadfile(lua_State* L, const char* filename) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_loadfile_t>("luaL_loadfile")(L, filename);
}

/// <summary>
/// Loads a buffer.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="buff">The buffer.</param>
/// <param name="sz">The size.</param>
/// <param name="name">The name.</param>
/// <returns></returns>
inline int luaL_loadbuffer(lua_State* L, const char* buff, size_t sz,
	const char* name) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_loadbuffer_t>("luaL_loadbuffer")(L, buff, sz, name);
}

/// <summary>
/// Loads a string.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="s">The string.</param>
/// <returns></returns>
inline int luaL_loadstring(lua_State* L, const char* s) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_loadstring_t>("luaL_loadstring")(L, s);
}

/// <summary>
/// Creates a new state.
/// </summary>
/// <returns>The state.</returns>
inline lua_State* luaL_newstate() {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_newstate_t>("luaL_newstate")();
}

/// <summary>
/// Gsubs, replaces a string.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="s">The string.</param>
/// <param name="p">The pattern.</param>
/// <param name="r">The replacement.</param>
/// <returns>The string.</returns>
inline const char* luaL_gsub(lua_State* L, const char* s, const char* p,
	const char* r) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_gsub_t>("luaL_gsub")(L, s, p, r);
}

/// <summary>
/// Finds a table.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="idx">The index.</param>
/// <param name="fname">The name.</param>
/// <param name="szhint">The size hint.</param>
/// <returns>The name.</returns>
inline const char* luaL_findtable(lua_State* L, int idx,
	const char* fname, int szhint) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_findtable_t>("luaL_findtable")(L, idx, fname, szhint);
}

/// ============================= ///
/// Buffer functions (stack -> C) ///
/// ============================= ///

/// <summary>
/// Initializes the buffer.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="B">The buffer.</param>
/// <returns></returns>
inline void luaL_buffinit(lua_State* L, luaL_Buffer* B) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_buffinit_t>("luaL_buffinit")(L, B);
}

/// <summary>
/// Prepares the buffer.
/// </summary>
/// <param name="B">The buffer.</param>
/// <returns>The buffer.</returns>
inline char* luaL_prepbuffer(luaL_Buffer* B) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_prepbuffer_t>("luaL_prepbuffer")(B);
}

/// <summary>
/// Adds a string to the buffer.
/// </summary>
/// <param name="B">The buffer.</param>
/// <param name="s">The string.</param>
/// <param name="l">The length.</param>
/// <returns></returns>
inline void luaL_addlstring(luaL_Buffer* B, const char* s, size_t l) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_addlstring_t>("luaL_addlstring")(B, s, l);
}

/// <summary>
/// Adds a string to the buffer.
/// </summary>
/// <param name="B">The buffer.</param>
/// <param name="s">The string.</param>
/// <returns></returns>
inline void luaL_addstring(luaL_Buffer* B, const char* s) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_addstring_t>("luaL_addstring")(B, s);
}

/// <summary>
/// Adds a value to the buffer.
/// </summary>
/// <param name="B">The buffer.</param>
/// <returns></returns>
inline void luaL_addvalue(luaL_Buffer* B) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_addvalue_t>("luaL_addvalue")(B);
}

/// <summary>
/// Pushes the result.
/// </summary>
/// <param name="B">The buffer.</param>
/// <returns></returns>
inline void luaL_pushresult(luaL_Buffer* B) {
	using namespace Carbon::Lua::Prototypes;
	return GetFunc<luaL_pushresult_t>("luaL_pushresult")(B);
}

/// ============= ///
/// Useful macros ///
/// ============= ///

#define luaL_argcheck(L, cond,numarg,extramsg)	\
		((void)((cond) || luaL_argerror(L, (numarg), (extramsg))))
#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))
#define luaL_checkint(L,n)	((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L,n,d)	((int)luaL_optinteger(L, (n), (d)))
#define luaL_checklong(L,n)	((long)luaL_checkinteger(L, (n)))
#define luaL_optlong(L,n,d)	((long)luaL_optinteger(L, (n), (d)))

#define luaL_typename(L,i)	lua_typename(L, lua_type(L,(i)))

#define luaL_dofile(L, fn)	(luaL_loadfile(L, fn) || lua_pcall(L, 0, 0, 0))

#define luaL_dostring(L, s)	(luaL_loadstring(L, s) || lua_pcall(L, 0, 0, 0))

#define luaL_getmetatable(L,n)	(lua_getfield(L, LUA_REGISTRYINDEX, (n)))

#define luaL_opt(L,f,n,d)	(lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))

#define luaL_addchar(B,c) \
  ((void)((B)->p < (B)->buffer+LUAL_BUFFERSIZE || luaL_prepbuffer(B)), \
   (*(B)->p++ = (char)(c)))

#define luaL_putchar(B,c) luaL_addchar(B, c)
#define luaL_addsize(B,n)	((B)->p += (n))

#define lua_ref(L,lock) ((lock) ? luaL_ref(L, LUA_REGISTRYINDEX) : \
      (lua_pushstring(L, "unlocked references are obsolete"), lua_error(L), 0))

#define lua_unref(L,ref)        luaL_unref(L, LUA_REGISTRYINDEX, (ref))

#define lua_getref(L,ref)       lua_rawgeti(L, LUA_REGISTRYINDEX, (ref))

#define lua_reg 			luaL_Reg
