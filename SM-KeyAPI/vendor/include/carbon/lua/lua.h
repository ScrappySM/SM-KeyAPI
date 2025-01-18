/// Types/constants based off https://github.com/lua/lua/blob/v5.1/lua.h 
/// Made by Ben McAvoy for CarbonLib https://github.com/ScrappySM/CarbonLib

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
#include <cstdarg>
#include <stddef.h>

#define LUA_VERSION	"Lua 5.1.5 (JIT, Carbon bindings)"
#define LUA_VERSION_NUM	501
#define LUA_COPYRIGHT	"Copyright (C) 1994-2006 Lua.org, PUC-Rio"
#define LUA_AUTHORS 	"R. Ierusalimschy, L. H. de Figueiredo & W. Celes"

#define	LUA_SIGNATURE	"\033Lua"

#define LUA_MULTRET	(-1)

#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)
#define lua_upvalueindex(i)	(LUA_GLOBALSINDEX-(i))

#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRERR	5

#define LUA_GCSTOP		0
#define LUA_GCRESTART		1
#define LUA_GCCOLLECT		2
#define LUA_GCCOUNT		3
#define LUA_GCCOUNTB		4
#define LUA_GCSTEP		5
#define LUA_GCSETPAUSE		6
#define LUA_GCSETSTEPMUL	7

#define LUA_OK		0

#define LUA_IDSIZE	60

#define LUA_TNONE		(-1)

#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8

#define LUA_MINSTACK	20

#define LUA_NUMBER float
#define LUA_INTEGER ptrdiff_t

typedef struct lua_State lua_State;

typedef int (*lua_CFunction) (lua_State *L);

typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);

typedef int (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);

typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);

typedef LUA_NUMBER lua_Number;
typedef LUA_INTEGER lua_Integer;

typedef struct lua_Debug {
	int event;
	const char* name; /* (n) */
	const char* namewhat; /* (n) */
	const char* what; /* (S) */
	const char* source; /* (S) */
	int currentline; /* (l) */
	int linedefined; /* (S) */
	int lastlinedefined; /* (S) */
	unsigned char nups; /* (u) number of upvalues */
	unsigned char nparams; /* (u) number of parameters */
	char isvararg; /* (u) */
	char istailcall; /* (t) */
	short ftransfer; /* (r) */
	short ntransfer; /* (r) */
	char short_src[LUA_IDSIZE]; /* (S) */
	struct CallInfo* i_ci; /* active function */
} lua_Debug;

typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);

namespace Carbon::Lua::Prototypes {
	typedef lua_State* (lua_newstate_t)(lua_Alloc f, void* ud);
	typedef void (lua_close_t)(lua_State* L);
	typedef lua_State* (lua_newthread_t)(lua_State* L);
	typedef lua_CFunction(lua_atpanic_t)(lua_State* L, lua_CFunction panicf);
	typedef int (lua_gettop_t)(lua_State* L);
	typedef void (lua_settop_t)(lua_State* L, int index);
	typedef void (lua_pushvalue_t)(lua_State* L, int index);
	typedef void (lua_remove_t)(lua_State* L, int index);
	typedef void (lua_insert_t)(lua_State* L, int index);
	typedef void (lua_replace_t)(lua_State* L, int index);
	typedef int (lua_checkstack_t)(lua_State* L, int sz);

	typedef void (lua_xmove_t)(lua_State* from, lua_State* to, int n);

	typedef int (lua_isnumber_t)(lua_State* L, int index);
	typedef int (lua_isstring_t)(lua_State* L, int index);
	typedef int (lua_iscfunction_t)(lua_State* L, int index);
	typedef int (lua_isuserdata_t)(lua_State* L, int index);
	typedef int (lua_type_t)(lua_State* L, int index);
	typedef const char* (lua_typename_t)(lua_State* L, int tp);

	typedef int (lua_equal_t)(lua_State* L, int index1, int index2);
	typedef int (lua_rawequal_t)(lua_State* L, int index1, int index2);
	typedef int (lua_lessthan_t)(lua_State* L, int index1, int index2);

	typedef lua_Number(lua_tonumber_t)(lua_State* L, int index);
	typedef lua_Integer(lua_tointeger_t)(lua_State* L, int index);
	typedef int (lua_toboolean_t)(lua_State* L, int index);
	typedef const char* (lua_tolstring_t)(lua_State* L, int index, size_t* len);
	typedef size_t(lua_objlen_t)(lua_State* L, int index);
	typedef lua_CFunction(lua_tocfunction_t)(lua_State* L, int index);
	typedef void* (lua_touserdata_t)(lua_State* L, int index);
	typedef lua_State* (lua_tothread_t)(lua_State* L, int index);
	typedef const void* (lua_topointer_t)(lua_State* L, int index);

	typedef void (lua_pushnil_t)(lua_State* L);
	typedef void (lua_pushnumber_t)(lua_State* L, lua_Number n);
	typedef void (lua_pushinteger_t)(lua_State* L, lua_Integer n);
	typedef void (lua_pushlstring_t)(lua_State* L, const char* s, size_t l);
	typedef void (lua_pushstring_t)(lua_State* L, const char* s);
	typedef const char* (lua_pushvfstring_t)(lua_State* L, const char* fmt, va_list argp);
	typedef const char* (lua_pushfstring_t)(lua_State* L, const char* fmt, ...);
	typedef void (lua_pushcclosure_t)(lua_State* L, lua_CFunction fn, int n);
	typedef void (lua_pushboolean_t)(lua_State* L, int b);
	typedef void (lua_pushlightuserdata_t)(lua_State* L, void* p);
	typedef int (lua_pushthread_t)(lua_State* L);

	typedef void (lua_gettable_t)(lua_State* L, int index);
	typedef void (lua_getfield_t)(lua_State* L, int index, const char* k);
	typedef void (lua_rawget_t)(lua_State* L, int index);
	typedef void (lua_rawgeti_t)(lua_State* L, int index, int n);
	typedef void (lua_createtable_t)(lua_State* L, int narr, int nrec);
	typedef void* (lua_newuserdata_t)(lua_State* L, size_t sz);
	typedef int (lua_getmetatable_t)(lua_State* L, int objindex);
	typedef void (lua_getfenv_t)(lua_State* L, int index);

	typedef void (lua_settable_t)(lua_State* L, int index);
	typedef void (lua_setfield_t)(lua_State* L, int index, const char* k);
	typedef void (lua_rawset_t)(lua_State* L, int index);
	typedef void (lua_rawseti_t)(lua_State* L, int index, int n);
	typedef int (lua_setmetatable_t)(lua_State* L, int objindex);
	typedef int (lua_setfenv_t)(lua_State* L, int index);

	typedef void (lua_call_t)(lua_State* L, int nargs, int nresults);
	typedef int (lua_pcall_t)(lua_State* L, int nargs, int nresults, int errfunc);
	typedef int (lua_cpcall_t)(lua_State* L, lua_CFunction func, void* ud);
	typedef int (lua_load_t)(lua_State* L, lua_Reader reader, void* dt, const char* chunkname);
	typedef int (lua_dump_t)(lua_State* L, lua_Writer writer, void* data);

	typedef int (lua_yield_t)(lua_State* L, int nresults);
	typedef int (lua_resume_t)(lua_State* L, int narg);
	typedef int (lua_status_t)(lua_State* L);

	typedef int (lua_gc_t)(lua_State* L, int what, int data);

	typedef int (lua_error_t)(lua_State* L);

	typedef int (lua_next_t)(lua_State* L, int index);

	typedef void (lua_concat_t)(lua_State* L, int n);

	typedef lua_Alloc(lua_getallocf_t)(lua_State* L, void** ud);
	typedef void (lua_setallocf_t)(lua_State* L, lua_Alloc f, void* ud);

	typedef int lua_getstack_t(lua_State* L, int level, lua_Debug* ar);
	typedef int lua_getinfo_t(lua_State* L, const char* what, lua_Debug* ar);
	typedef const char* lua_getlocal_t(lua_State* L, const lua_Debug* ar, int n);
	typedef const char* lua_setlocal_t(lua_State* L, const lua_Debug* ar, int n);
	typedef const char* lua_getupvalue_t(lua_State* L, int funcindex, int n);
	typedef const char* lua_setupvalue_t(lua_State* L, int funcindex, int n);

	typedef int lua_sethook_t(lua_State* L, lua_Hook func, int mask, int count);
	typedef lua_Hook lua_gethook_t(lua_State* L);
	typedef int lua_gethookmask_t(lua_State* L);
	typedef int lua_gethookcount_t(lua_State* L);
} // namespace Carbon::Lua::Prototypes

template <typename T>
inline T* GetFunc(const char* name) {
	static auto luaHandle = GetModuleHandle("lua51.dll");
	if (!luaHandle) {
		return nullptr;
	}

	return reinterpret_cast<T*>(GetProcAddress(luaHandle, name));
}

/// ================== ///
/// State manipulation ///
/// ================== ///

/// <summary>
/// Creates a new Lua state.
/// </summary>
/// <param name="f">The allocator function.</param>
/// <param name="ud">The user data.</param>
/// <returns>The new Lua state.</returns>
inline lua_State* lua_newstate(lua_Alloc f, void* ud) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_newstate_t>("lua_newstate");
	return fn(f, ud);
}

/// <summary>
/// Closes a Lua state and frees all memory associated with it.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns></returns>
inline void lua_close(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_close_t>("lua_close");
	return fn(L);
}

/// <summary>
/// Creates a new thread.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The new thread.</returns>
inline lua_State* lua_newthread(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_newthread_t>("lua_newthread");
	return fn(L);
}

/// <summary>
/// Sets the panic function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="panicf">The panic function.</param>
/// <returns>The old panic function.</returns>
inline lua_CFunction lua_atpanic(lua_State* L, lua_CFunction panicf) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_atpanic_t>("lua_atpanic");
	return fn(L, panicf);
}

/// ================== ///
/// Stack manipulation ///
/// ================== ///

/// <summary>
/// Gets the top index of the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The top index of the stack.</returns>
inline int lua_gettop(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_gettop_t>("lua_gettop");
	return fn(L);
}

/// <summary>
/// Sets the top index of the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns></returns>
inline void lua_settop(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_settop_t>("lua_settop");
	return fn(L, index);
}

/// <summary>
/// Pushes a value onto the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns></returns>
inline void lua_pushvalue(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushvalue_t>("lua_pushvalue");
	return fn(L, index);
}

/// <summary>
/// Removes a value from the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns></returns>
inline void lua_remove(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_remove_t>("lua_remove");
	return fn(L, index);
}

/// <summary>
/// Inserts a value into the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns></returns>
inline void lua_insert(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_insert_t>("lua_insert");
	return fn(L, index);
}

/// <summary>
/// Replaces a value in the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns></returns>
inline void lua_replace(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_replace_t>("lua_replace");
	return fn(L, index);
}

/// <summary>
/// Grows the stack size to top + sz elements, raising an error if the stack cannot grow to that size. msg is an additional text to go into the error message. 
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="sz">The size.</param>
/// <returns>1 if there is enough space, 0 otherwise.</returns>
inline int lua_checkstack(lua_State* L, int sz) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_checkstack_t>("lua_checkstack");
	return fn(L, sz);
}

/// <summary>
/// Moves values between Lua states.
/// Exchanges values between different threads of the same global state.
/// This function pops `n` values from the `from` stack and pushes them onto the `to` stack.
/// </summary>
/// <param name="from">The source Lua state.</param>
/// <param name="to">The destination Lua state.</param>
/// <param name="n">The number of values to move.</param>
/// <returns></returns>
inline void lua_xmove(lua_State* from, lua_State* to, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_xmove_t>("lua_xmove");
	return fn(from, to, n);
}

/// ============================= ///
/// Access functions (stack -> C) ///
/// ============================= ///

/// <summary>
/// Checks if the value at the index is a number.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>1 if the value is a number, 0 otherwise.</returns>
inline int lua_isnumber(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_isnumber_t>("lua_isnumber");
	return fn(L, index);
}

/// <summary>
/// Checks if the value at the index is a string.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>1 if the value is a string, 0 otherwise.</returns>
inline int lua_isstring(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_isstring_t>("lua_isstring");
	return fn(L, index);
}

/// <summary>
/// Checks if the value at the index is a C function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>1 if the value is a C function, 0 otherwise.</returns>
inline int lua_iscfunction(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_iscfunction_t>("lua_iscfunction");
	return fn(L, index);
}

/// <summary>
/// Checks if the value at the index is a user data.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>1 if the value is a user data (full or light), 0 otherwise.</returns>
inline int lua_isuserdata(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_isuserdata_t>("lua_isuserdata");
	return fn(L, index);
}

/// <summary>
/// Gets the type of the value at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The type of the value (LUA_TNIL, LUA_TBOOLEAN, LUA_TLIGHTUSERDATA, LUA_TNUMBER, LUA_TSTRING, LUA_TTABLE, LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD).</returns>
inline int lua_type(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_type_t>("lua_type");
	return fn(L, index);
}

/// <summary>
/// Gets the type name of the value at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="tp">The type, must be a valid type from `lua_type`.</param>
/// <returns>The type name as a string literal.</returns>
inline const char* lua_typename(lua_State* L, int tp) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_typename_t>("lua_typename");
	return fn(L, tp);
}

/// <summary>
/// Checks if two values on the stack are equal.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index1">The first index.</param>
/// <param name="index2">The second index.</param>
/// <returns>1 if the values are equal, 0 otherwise.</returns>
inline int lua_equal(lua_State* L, int index1, int index2) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_equal_t>("lua_equal");
	return fn(L, index1, index2);
}

/// <summary>
/// Checks if two values on the stack are equal without metamethods.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index1">The first index.</param>
/// <param name="index2">The second index.</param>
/// <returns>1 if the values are equal, 0 otherwise.</returns>
inline int lua_rawequal(lua_State* L, int index1, int index2) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_rawequal_t>("lua_rawequal");
	return fn(L, index1, index2);
}

/// <summary>
/// Checks if the first value is less than the second value.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index1">The first index.</param>
/// <param name="index2">The second index.</param>
/// <returns>1 if the first value is less than the second value, 0 otherwise.</returns>
inline int lua_lessthan(lua_State* L, int index1, int index2) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_lessthan_t>("lua_lessthan");
	return fn(L, index1, index2);
}

/// <summary>
/// Converts the value at the index to a number.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The number as a `lua_Number` (default float), returns 0 if the value is not a number.</returns>
inline lua_Number lua_tonumber(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_tonumber_t>("lua_tonumber");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to an integer.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The integer as a `lua_Integer` (default ptrdiff_t).</returns>
inline lua_Integer lua_tointeger(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_tointeger_t>("lua_tointeger");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to a boolean.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The boolean as an integer (0 or 1), anything other than `false` and `nil` is true.</returns>
inline int lua_toboolean(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_toboolean_t>("lua_toboolean");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to a string.
/// This string always has a zero ('\0') after the last character.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <param name="len">The length of the string.</param>
/// <returns>The string as a `const char*`.</returns>
inline const char* lua_tolstring(lua_State* L, int index, size_t* len) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_tolstring_t>("lua_tolstring");
	return fn(L, index, len);
}

/// <summary>
/// Gets the length of the value at the index.
/// Only works on strings and tables
/// Same as the `#` operator in Lua.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The length of the value, returns 0 for other types.</returns>
inline size_t lua_objlen(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_objlen_t>("lua_objlen");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to a C function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The C function as a `lua_CFunction`, if it's not a C function, returns `nullptr`.</returns>
inline lua_CFunction lua_tocfunction(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_tocfunction_t>("lua_tocfunction");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to user data.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The user data as a `void*`, full userdata returns block address, light returns pointer, otherwise returns `nullptr`.</returns>
inline void* lua_touserdata(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_touserdata_t>("lua_touserdata");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to a thread.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The thread as a `lua_State*`, returning `nullptr` if the value is not a thread.</returns>
inline lua_State* lua_tothread(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_tothread_t>("lua_tothread");
	return fn(L, index);
}

/// <summary>
/// Converts the value at the index to a pointer.
/// The value can be a userdata, table, thread or a function. Otherwise, returns NULL.
/// Typically only used for debugging.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index.</param>
/// <returns>The pointer as a `const void*`, `nullptr` if the value is not a userdata, table, thread or function.</returns>
inline const void* lua_topointer(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_topointer_t>("lua_topointer");
	return fn(L, index);
}

/// =========================== ///
/// Push functions (C -> stack) ///
/// =========================== ///

/// <summary>
/// Pushes a nil value onto the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns></returns>
inline void lua_pushnil(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushnil_t>("lua_pushnil");
	return fn(L);
}

/// <summary>
/// Pushes a number onto the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="n">The number.</param>
/// <returns></returns>
inline void lua_pushnumber(lua_State* L, lua_Number n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushnumber_t>("lua_pushnumber");
	return fn(L, n);
}

/// <summary>
/// Pushes an integer onto the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="n">The integer.</param>
/// <returns></returns>
inline void lua_pushinteger(lua_State* L, lua_Integer n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushinteger_t>("lua_pushinteger");
	return fn(L, n);
}

/// <summary>
/// Pushes a string onto the stack.
/// Lua will make a copy of the string, so the memory at `s` can be freed or reused immediately after the function returns.
/// This string can contain embedded zeros, as there is no null termination check.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="s">The string.</param>
/// <param name="l">The length of the string.</param>
/// <returns></returns>
inline void lua_pushlstring(lua_State* L, const char* s, size_t l) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushlstring_t>("lua_pushlstring");
	return fn(L, s, l);
}

/// <summary>
/// Pushes a string onto the stack.
/// Lua will make a copy of the string, so the memory at `s` can be freed or reused immediately after the function returns.
/// The string cannot contain embedded zeros; it is assumed to end at the first zero (null terminator).
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="s">The string.</param>
/// <returns></returns>
inline void lua_pushstring(lua_State* L, const char* s) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushstring_t>("lua_pushstring");
	return fn(L, s);
}

/// <summary>
/// Pushes a formatted string onto the stack.
/// Equivalent to `lua_pushfstring` except that it receives a va_list instead of a variable number of arguments.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="fmt">The format string.</param>
/// <param name="argp">The arguments.</param>
inline const char* lua_pushvfstring(lua_State* L, const char* fmt, va_list argp) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushvfstring_t>("lua_pushvfstring");
	return fn(L, fmt, argp);
}

/// <summary>
/// Pushes a formatted string onto the stack.
/// You do not have to allocate space for the string; the result is a pointer to a string inside the Lua state.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="fmt">The format string.</param>
/// <param name="...">The arguments.</param>
/// <returns>The formatted string.</returns>
inline const char* lua_pushfstring(lua_State* L, const char* fmt, ...) {
	using namespace Carbon::Lua::Prototypes;
	va_list argp;
	va_start(argp, fmt);
	static auto fn = GetFunc<lua_pushvfstring_t>("lua_pushvfstring");
	const char* ret = fn(L, fmt, argp);
	va_end(argp);
	return ret;
}

/// <summary>
/// Pushes a C function onto the stack.
/// When a C function is created, it is possible to associate some values with it thus creating a C closure; these values are then accessible to the function whenever it is called.
/// To associate values with a C function, first push those values onto the stack (one by one) using `lua_pushnumber`, `lua_pushstring`, etc.
/// Then push the function onto the stack; using `lua_pushcclosure`, you can create a C closure.
/// This also pops the values from the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="fn">The C function.</param>
/// <param name="n">The number of upvalues.</param>
/// <returns></returns>
inline void lua_pushcclosure(lua_State* L, lua_CFunction fn, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto l_fn = GetFunc<lua_pushcclosure_t>("lua_pushcclosure");
	return l_fn(L, fn, n);
}

/// <summary>
/// Pushes a boolean onto the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="b">The boolean.</param>
/// <returns></returns>
inline void lua_pushboolean(lua_State* L, int b) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushboolean_t>("lua_pushboolean");
	return fn(L, b);
}

/// <summary>
/// Pushes a light user data onto the stack.
/// Userdata represents C values in Lua. A *light* userdata represents a pointer.
/// You do not create it, it has no metatable and it is not collected by the garbage collector as it is never created by Lua.
/// It is equal to any other light userdata with the same C address.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="p">The light user data.</param>
/// <returns></returns>
inline void lua_pushlightuserdata(lua_State* L, void* p) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushlightuserdata_t>("lua_pushlightuserdata");
	return fn(L, p);
}

/// <summary>
/// Pushes the current thread onto the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>1 if the thread is the main thread, 0 otherwise.</returns>
inline int lua_pushthread(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pushthread_t>("lua_pushthread");
	return fn(L);
}

/// ============================== ///
/// Get functions (stack -> stack) ///
/// ============================== ///

/// <summary>
/// Gets a value from the table at the index.
/// Pushes onto the stack value `t[n]`.
/// This function pops the key from the stack.
/// May trigger a metamethod index event in Lua nature.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <returns></returns>
inline void lua_gettable(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_gettable_t>("lua_gettable");
	return fn(L, index);
}

/// <summary>
/// Gets a value from the table at the index with the key.
/// Pushes onto the stack value `t[k]`.
/// This may trigger a metamethod index event in Lua nature.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <param name="k">The key.</param>
/// <returns></returns>
inline void lua_getfield(lua_State* L, int index, const char* k) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getfield_t>("lua_getfield");
	return fn(L, index, k);
}

/// <summary>
/// Gets a value from the table at the index.
/// Similar to `lua_gettable`, but does not trigger metamethods.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <returns></returns>
inline void lua_rawget(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_rawget_t>("lua_rawget");
	return fn(L, index);
}

/// <summary>
/// Gets a value from the table at the index with the integer key.
/// Pushes onto the stack value `t[n]`.
/// This may trigger a metamethod index event in Lua nature.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <param name="n">The integer key.</param>
/// <returns></returns>
inline void lua_rawgeti(lua_State* L, int index, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_rawgeti_t>("lua_rawgeti");
	return fn(L, index, n);
}

/// <summary>
/// Creates a new empty table and pushes it onto the stack.
/// The new table has space pre-allocated for narr array elements and nrec non-array elements.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="narr">The number of array elements.</param>
/// <param name="nrec">The number of non-array elements.</param>
/// <returns></returns>
inline void lua_createtable(lua_State* L, int narr, int nrec) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_createtable_t>("lua_createtable");
	return fn(L, narr, nrec);
}

/// <summary>
/// Creates a new full userdata and pushes it onto the stack.
/// The memory is allocated and managed by the user.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="sz">The size of the userdata.</param>
/// <returns>The pointer to the userdata.</returns>
inline void* lua_newuserdata(lua_State* L, size_t sz) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_newuserdata_t>("lua_newuserdata");
	return fn(L, sz);
}

/// <summary>
/// Gets the metatable of the value at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="objindex">The index of the value.</param>
/// <returns>1 if the value has a metatable, 0 otherwise.</returns>
inline int lua_getmetatable(lua_State* L, int objindex) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getmetatable_t>("lua_getmetatable");
	return fn(L, objindex);
}

/// <summary>
/// Gets the environment of the value at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the value.</param>
/// <returns></returns>
inline void lua_getfenv(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getfenv_t>("lua_getfenv");
	return fn(L, index);
}

/// ============================== ///
/// Set functions (stack -> stack) ///
/// ============================== ///

/// <summary>
/// Sets a value in the table at the index.
/// Does the equivalent of `t[n] = v`, where `t` is the value at the index and `v` is the value at the top of the stack.
/// This may trigger a metamethod newindex event in Lua nature.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <returns></returns>
inline void lua_settable(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_settable_t>("lua_settable");
	return fn(L, index);
}

/// <summary>
/// Sets a value in the table at the index with the key.
/// Does the equivalent of `t[k] = v`, where `t` is the value at the index and `v` is the value at the top of the stack.
/// This may trigger a metamethod newindex event in Lua nature.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <param name="k">The key.</param>
/// <returns></returns>
inline void lua_setfield(lua_State* L, int index, const char* k) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_setfield_t>("lua_setfield");
	return fn(L, index, k);
}

/// <summary>
/// Sets a value in the table at the index.
/// Similar to `lua_settable`, but does not trigger metamethods.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <returns></returns>
inline void lua_rawset(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_rawset_t>("lua_rawset");
	return fn(L, index);
}

/// <summary>
/// Sets a value in the table at the index with the integer key.
/// Does the equivalent of `t[n] = v`, where `t` is the value at the index and `v` is the value at the top of the stack.
/// This may trigger a metamethod newindex event in Lua nature.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <param name="n">The integer key.</param>
/// <returns></returns>
inline void lua_rawseti(lua_State* L, int index, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_rawseti_t>("lua_rawseti");
	return fn(L, index, n);
}

/// <summary>
/// Sets the metatable of the value at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="objindex">The index of the value.</param>
/// <returns>1 if the value has a metatable, 0 otherwise.</returns>
inline int lua_setmetatable(lua_State* L, int objindex) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_setmetatable_t>("lua_setmetatable");
	return fn(L, objindex);
}

/// <summary>
/// Sets the environment of the value at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the value.</param>
/// <returns></returns>
inline int lua_setfenv(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_setfenv_t>("lua_setfenv");
	return fn(L, index);
}

/// ============== ///
/// Call functions ///
/// ============== ///

/// <summary>
/// Calls a function.
/// To call a function you must use the following protocol: first, the function to be called is pushed onto the stack; then, the arguments to the function are pushed in direct order; that is, the first argument is pushed first.
/// Finally you call `lua_call`; `nargs` is the number of arguments that you pushed onto the stack.
/// All arguments and the function value are popped from the stack when the function is called.
/// The function results are pushed onto the stack when the function returns.
/// The number of results is adjusted to `nresults`, unless `nresults` is `LUA_MULTRET`.
/// In this case, all results from the function are pushed.
/// Lua takes care that the returned values fit into the stack space.
/// The function results are pushed onto the stack in direct order (the first result is pushed first), so that after the call the last result is on the top of the stack.
/// Any error inside the called function is propagated upwards (with a longjmp).
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="nargs">The number of arguments.</param>
/// <param name="nresults">The number of results.</param>
/// <returns></returns>
inline void lua_call(lua_State* L, int nargs, int nresults) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_call_t>("lua_call");
	return fn(L, nargs, nresults);
}

/// <summary>
/// Calls a function in protected mode.
/// If the function `func` calls `lua_error`, the return value is the error code.
/// Otherwise, the return value is `LUA_OK`.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="nargs">The number of arguments.</param>
/// <param name="nresults">The number of results.</param>
/// <param name="errfunc">The error function index.</param>
/// <returns></returns>
inline int lua_pcall(lua_State* L, int nargs, int nresults, int errfunc) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_pcall_t>("lua_pcall");
	return fn(L, nargs, nresults, errfunc);
}

/// <summary>
/// Calls a function in protected mode.
///	Similar to `lua_pcall`, but allows the called function to yield (see `lua_yield`).
/// If the function `func` calls `lua_error`, the return value is the error code.
/// Otherwise, the return value is `LUA_OK`.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="func">The C function.</param>
/// <param name="ud">The user data.</param>
/// <returns></returns>
inline int lua_cpcall(lua_State* L, lua_CFunction func, void* ud) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_cpcall_t>("lua_cpcall");
	return fn(L, func, ud);
}

/// <summary>
/// Loads a Lua chunk.
/// If there are no errors, `lua_load` pushes the compiled chunk as a Lua function on top of the stack.
/// Otherwise, it pushes an error message.
/// The return value is the error code.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="reader">The reader function.</param>
/// <param name="dt">The data.</param>
/// <param name="chunkname">The chunk name.</param>
/// <returns></returns>
inline int lua_load(lua_State* L, lua_Reader reader, void* dt, const char* chunkname) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_load_t>("lua_load");
	return fn(L, reader, dt, chunkname);
}

/// <summary>
/// Dumps a function as a binary chunk.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="writer">The writer function.</param>
/// <param name="data">The data.</param>
/// <returns></returns>
inline int lua_dump(lua_State* L, lua_Writer writer, void* data) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_dump_t>("lua_dump");
	return fn(L, writer, data);
}

/// ================== ///
/// Coroutine functions ///
/// ================== ///

/// <summary>
/// Yields a coroutine.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="nresults">The number of results.</param>
/// <returns></returns>
inline int lua_yield(lua_State* L, int nresults) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_yield_t>("lua_yield");
	return fn(L, nresults);
}

/// <summary>
/// Resumes a coroutine.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="narg">The number of arguments.</param>
/// <returns>The status of the coroutine.</returns>
/// <remarks>
inline int lua_resume(lua_State* L, int narg) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_resume_t>("lua_resume");
	return fn(L, narg);
}

/// <summary>
/// Returns the status of the coroutine.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The status of the coroutine.</returns>
inline int lua_status(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_status_t>("lua_status");
	return fn(L);
}

/// ================== ///
/// Garbage collection ///
/// ================== ///

/// <summary>
/// Controls the garbage collector.
///    LUA_GCSTOP: stops the garbage collector.
///    LUA_GCRESTART: restarts the garbage collector.
///    LUA_GCCOLLECT: performs a full garbage-collection cycle.
///    LUA_GCCOUNT: returns the current amount of memory (in Kbytes) in use by Lua.
///    LUA_GCCOUNTB: returns the remainder of dividing the current amount of bytes of memory in use by Lua by 1024.
///    LUA_GCSTEP: performs an incremental step of garbage collection. The step "size" is controlled by data (larger values mean more steps) in a non-specified way. If you want to control the step size you must experimentally tune the value of data. The function returns 1 if the step finished a garbage-collection cycle.
///    LUA_GCSETPAUSE: sets data as the new value for the pause of the collector (see §2.10). The function returns the previous value of the pause.
///    LUA_GCSETSTEPMUL: sets data as the new value for the step multiplier of the collector (see §2.10). The function returns the previous value of the step multiplier.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="what">The action.</param>
/// <param name="data">The data.</param>
/// <returns></returns>
inline int lua_gc(lua_State* L, int what, int data) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_gc_t>("lua_gc");
	return fn(L, what, data);
}

/// ======================= ///
/// Miscellaneous functions ///
/// ======================= ///

/// <summary>
/// Reports an error.
/// The error message is on the top of the stack.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns></returns>
inline int lua_error(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_error_t>("lua_error");
	return fn(L);
}

/// <summary>
/// Pops a key from the stack, and pushes a key-value pair from the table at the index.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="index">The index of the table.</param>
/// <returns></returns>
inline int lua_next(lua_State* L, int index) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_next_t>("lua_next");
	return fn(L, index);
}

/// <summary>
/// Concatenates the `n` values at the top of the stack, pops them, and leaves the result at the top.
/// If `n` is 1, the result is the single value on the stack (that is, the function does nothing).
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="n">The number of values.</param>
/// <returns></returns>
inline void lua_concat(lua_State* L, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_concat_t>("lua_concat");
	return fn(L, n);
}

/// <summary>
/// Returns the memory allocated for the Lua state.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The memory allocated for the Lua state.</returns>
inline lua_Alloc lua_getallocf(lua_State* L, void** ud) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getallocf_t>("lua_getallocf");
	return fn(L, ud);
}

/// <summary>
/// Sets the memory allocator function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="f">The allocator function.</param>
/// <param name="ud">The user data.</param>
/// <returns></returns>
inline void lua_setallocf(lua_State* L, lua_Alloc f, void* ud) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_setallocf_t>("lua_setallocf");
	return fn(L, f, ud);
}

/// ====== ///
/// Macros ///
/// ====== ///

#define lua_pop(L, n) lua_settop(L, -(n)-1)
#define lua_newtable(L) lua_createtable(L, 0, 0)
#define lua_register(L, n, f) (lua_pushcfunction(L, f), lua_setglobal(L, n))
#define lua_pushcfunction(L, f) lua_pushcclosure(L, f, 0)
#define lua_strlen(L, i) lua_objlen(L, i)
#define lua_isfunction(L, n) (lua_type(L, n) == LUA_TFUNCTION)
#define lua_istable(L, n) (lua_type(L, n) == LUA_TTABLE)
#define lua_islightuserdata(L, n) (lua_type(L, n) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L, n) (lua_type(L, n) == LUA_TNIL)
#define lua_isboolean(L, n) (lua_type(L, n) == LUA_TBOOLEAN)
#define lua_isthread(L, n) (lua_type(L, n) == LUA_TTHREAD)
#define lua_isnone(L, n) (lua_type(L, n) == LUA_TNONE)
#define lua_isnoneornil(L, n) (lua_type(L, n) <= 0)
#define lua_pushliteral(L, s) lua_pushstring(L, "" s, (sizeof(s)/sizeof(char))-1)
#define lua_setglobal(L, s) lua_setfield(L, LUA_GLOBALSINDEX, s)
#define lua_getglobal(L, s) lua_getfield(L, LUA_GLOBALSINDEX, s)
#define lua_tostring(L, i) lua_tolstring(L, i, nullptr)

#define lua_open() luaL_newstate()
#define lua_getregistry(L) lua_pushvalue(L, LUA_REGISTRYINDEX)
#define lua_getgccount(L) lua_gc(L, LUA_GCCOUNT, 0)

#define lua_Chunkreader lua_Reader
#define lua_Chunkwriter lua_Writer

/// ============= ///
/// Debugging API ///
/// ============= ///

/// <summary>
/// Get information about the interpreter runtime stack. 
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="ar">The debug information.</param>
/// <returns></returns>
inline int lua_getstack(lua_State* L, int level, lua_Debug* ar) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getstack_t>("lua_getstack");
	return fn(L, level, ar);
}

/// <summary>
/// Get information about a specific function/function call.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="ar">The debug information.</param>
/// <param name="what">The information to get (source, line, name, namewhat, etc).</param>
/// <returns>0 on error</returns>
inline int lua_getinfo(lua_State* L, const char* what, lua_Debug* ar) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getinfo_t>("lua_getinfo");
	return fn(L, what, ar);
}

/// <summary>
/// Get information about a local variable of a given activation record.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="ar">The debug information.</param>
/// <param name="n">The index of the local variable.</param>
/// <returns>The name of the local variable.</returns>
inline const char* lua_getlocal(lua_State* L, const lua_Debug* ar, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getlocal_t>("lua_getlocal");
	return fn(L, ar, n);
}

/// <summary>
/// Set the value of a local variable of a given activation record.
/// Assigns the value at the top of the stack to the variable and returns its name. It also pops the value from the stack. 
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="ar">The debug information.</param>
/// <param name="n">The index of the local variable.</param>
/// <returns>The name of the local variable.</returns>
inline const char* lua_setlocal(lua_State* L, const lua_Debug* ar, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_setlocal_t>("lua_setlocal");
	return fn(L, ar, n);
}

/// <summary>
/// Gets information about a closure's upvalue. (For Lua functions, upvalues are the external local variables that the function uses, and that are consequently included in its closure.)
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="funcindex">The index of the function.</param>
/// <param name="n">The index of the upvalue.</param>
/// <returns>The name of the upvalue.</returns>
inline const char* lua_getupvalue(lua_State* L, int funcindex, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_getupvalue_t>("lua_getupvalue");
	return fn(L, funcindex, n);
}

/// <summary>
/// Sets the value of a closure's upvalue. (For Lua functions, upvalues are the external local variables that the function uses, and that are consequently included in its closure.)
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="funcindex">The index of the function.</param>
/// <param name="n">The index of the upvalue.</param>
/// <returns>The name of the upvalue.</returns>
inline const char* lua_setupvalue(lua_State* L, int funcindex, int n) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_setupvalue_t>("lua_setupvalue");
	return fn(L, funcindex, n);
}

/// <summary>
/// Sets the debug hook function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="func">The debug hook function.</param>
/// <param name="mask">The mask.</param>
/// <param name="count">The count.</param>
/// <returns>1 if the hook was set, 0 otherwise.</returns>
inline int lua_sethook(lua_State* L, lua_Hook func, int mask, int count) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_sethook_t>("lua_sethook");
	return fn(L, func, mask, count);
}

/// <summary>
/// Gets the debug hook function.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The debug hook function.</returns>
inline lua_Hook lua_gethook(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_gethook_t>("lua_gethook");
	return fn(L);
}

/// <summary>
/// Gets the debug hook mask.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The debug hook mask.</returns>
inline int lua_gethookmask(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_gethookmask_t>("lua_gethookmask");
	return fn(L);
}

/// <summary>
/// Gets the debug hook count.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The debug hook count.</returns>
inline int lua_gethookcount(lua_State* L) {
	using namespace Carbon::Lua::Prototypes;
	static auto fn = GetFunc<lua_gethookcount_t>("lua_gethookcount");
	return fn(L);
}
