/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef __US_CALL_FROM_LUA
#define __US_CALL_FROM_LUA

#include <array>
#include <cinttypes>
#include <lua.hpp>
#include <type_traits>
#include <string>

#include "FunctionTraits.h"
#include "LuaTypeConvert.h"
#include "format.h"


namespace ff
{
	template<typename F>
	struct call_from_lua_traits
	{
		static bool const is_mem_fun = std::is_member_function_pointer<F>::value;
		using arguments = typename function_traits<F>::arguments;

		static size_t const arg_count = std::tuple_size<arguments>::value - is_mem_fun;

		template<size_t Index, bool>
		struct tuple_element
		{
			using type = typename std::tuple_element<Index, arguments>::type;
		};

		template<size_t Index>
		struct tuple_element<Index, false>
		{
			using type = void;
		};

		template<size_t Index>
		using arg_type = typename tuple_element < Index + is_mem_fun, Index<arg_count >::type;

		template<size_t Index>
		using convert_type = typename std::remove_const<typename std::remove_reference<arg_type<Index>>::type>::type;

		template<size_t Index>
		static convert_type<Index> arg_from_lua(lua_State* L)
		{			
			return LuaTypeConvert<convert_type<Index>>::from_lua(L, (int32_t)Index - (int32_t)arg_count);
		}
	};
}

#endif
