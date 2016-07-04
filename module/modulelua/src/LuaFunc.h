/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_LUA_FUNC
#define _US_LUA_FUNC

#include "lua.hpp"
#include "FunctionTraits.h"
#include "CallFromLuaTraits.h"

namespace ff
{
	// luaµ÷ÓÃc++º¯Êý
	class LuaFunc
	{
	public:
		template<typename F, size_t ...Indices>
		static typename std::enable_if<is_void_return<F>::value>::type
			call_from_lua_impl(lua_State* L, F func, index_sequence<Indices...>)
		{
			func(call_from_lua_traits<F>::template arg_from_lua<Indices>(L)...);
			lua_pushnil(L);
		}

		template<typename F, size_t ...Indices>
		static typename std::enable_if<!is_void_return<F>::value>::type
			call_from_lua_impl(lua_State* L, F func, index_sequence<Indices...>)
		{
			typename function_traits<F>::return_type rv = func(call_from_lua_traits<F>::template arg_from_lua<Indices>(L)...);
			LuaTypeConvert<typename function_traits<F>::return_type>::push_lua(L, rv);
		}

		template<typename C, typename F, size_t ...Indices>
		static typename std::enable_if<is_void_return<F>::value>::type
			call_from_lua_impl_o(lua_State* L, C* c, F func, index_sequence<Indices...>)
		{
			(c->*func)(call_from_lua_traits<F>::template arg_from_lua<Indices>(L)...);
			lua_pushnil(L);
		}

		template<typename C, typename F, size_t ...Indices>
		static typename std::enable_if<!is_void_return<F>::value>::type
			call_from_lua_impl_o(lua_State* L, C* c, F func, index_sequence<Indices...>)
		{
			typename function_traits<F>::return_type rv = (c->*func)(call_from_lua_traits<F>::template arg_from_lua<Indices>(L)...);
			LuaTypeConvert<typename function_traits<F>::return_type>::push_lua(L, rv);
		}

	public:
		template<typename FUNC>
		static int funcWrap(lua_State* L)
		{
			FUNC func = (FUNC)lua_touserdata(L, lua_upvalueindex(1));

			using call_traits = call_from_lua_traits<FUNC>;
			call_from_lua_impl(L, func, make_index_sequence<call_traits::arg_count>());

			return 1;
		}

		template<typename C, typename FUNC>
		static int clfuncWrap(lua_State* L)
		{
			C* c;
			FUNC func;
			char* data = (char*)lua_touserdata(L, lua_upvalueindex(1));
			memcpy(&c, data, sizeof(C*));
			memcpy(&func, data + sizeof(C*), sizeof(FUNC));

			using call_traits = call_from_lua_traits<FUNC>;
			call_from_lua_impl_o(L, c, func, make_index_sequence<call_traits::arg_count>());

			return 1;
		}

		template<typename C, typename R, typename ...Args>
		static int mfuncWrap(lua_State* L)
		{
			C* c;
			typedef R(C::*FUNC)(Args...);
			FUNC func;

			char* data = (char*)lua_touserdata(L, lua_upvalueindex(1));
			memcpy(&func, data, sizeof(FUNC));

			c = LuaTypeConvert<C*>::from_lua(L, 1);

			using call_traits = call_from_lua_traits<FUNC>;
			call_from_lua_impl_o(L, c, func, make_index_sequence<call_traits::arg_count>());

			return 1;
		}
	};
}

#endif
