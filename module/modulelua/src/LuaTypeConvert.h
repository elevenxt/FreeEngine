/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef __US_LUA_TYPE_CONVERT
#define __US_LUA_TYPE_CONVERT

#include "lua.hpp"
#include <string>
#include <assert.h>
#include <cinttypes>

namespace ff
{
	static_assert(sizeof(lua_Integer) == sizeof(int64_t), "type error");

	template<typename T, typename Enable = void>
	struct LuaTypeConvert;

	template<>
	struct LuaTypeConvert<bool>
	{
		static bool is_valid(lua_State* L, int idx)
		{
			return lua_isboolean(L, idx);
		}

		static bool from_lua(lua_State* L, int idx)
		{
			if (!is_valid(L, idx))
			{
				lua_pushstring(L, "type not correct");
				lua_error(L);
				return false;
			}

			return lua_toboolean(L, idx) != 0;
		}

		static void push_lua(lua_State* L, bool value)
		{
			lua_pushboolean(L, value);
		}
	};

#define LuaTypeConvertInt(T)	\
	template<>	\
	struct LuaTypeConvert<T>	\
	{	\
		static bool is_valid(lua_State* L, int idx)	\
		{	\
			return lua_isnumber(L, idx) != 0;	\
		}	\
		static lua_Integer from_lua(lua_State* L, int idx)	\
		{	\
			if (!is_valid(L, idx))	\
			{	\
				lua_pushstring(L, "type not correct");	\
				lua_error(L);	\
				return false;	\
			}	\
			return lua_tointeger(L, idx);	\
		}	\
		static void push_lua(lua_State* L, lua_Integer value)	\
		{	\
			lua_pushinteger(L, value);	\
		}	\
	}	\

	LuaTypeConvertInt(int8_t);
	LuaTypeConvertInt(int16_t);
	LuaTypeConvertInt(int32_t);
	LuaTypeConvertInt(int64_t);

	template<>
	struct LuaTypeConvert<std::string>
	{
		static bool is_valid(lua_State* L, int idx)
		{
			return lua_isstring(L, idx) != 0;
		}

		static std::string from_lua(lua_State* L, int idx)
		{
			if (!is_valid(L, idx))
			{
				lua_pushstring(L, "type not correct");
				lua_error(L);
				return "";
			}

			size_t len = 0;
			const char* val = lua_tolstring(L, idx, &len);
			return std::string(val, len);
		}

		static void push_lua(lua_State* L, std::string value)
		{
			lua_pushlstring(L, value.c_str(), value.size());
		}
	};

	template<>
	struct LuaTypeConvert<void*>
	{
		static bool is_valid(lua_State* L, int idx)
		{
			return lua_isuserdata(L, idx) != 0;
		}

		static void* from_lua(lua_State* L, int idx)
		{
			if (!is_valid(L, idx))
			{
				lua_pushstring(L, "type not correct");
				lua_error(L);
				return 0;
			}

			return lua_touserdata(L, idx);
		}

		static void push_lua(lua_State* L, void* value)
		{
			lua_pushlightuserdata(L, value);
		}
	};
}

#define LUA_CONVERT_POINTERDATA(DATA)	\
		template<>	\
		struct LuaTypeConvert<DATA*>{	\
			static DATA* from_lua(lua_State* L, int idx){	\
				DATA** data = (DATA**)lua_touserdata(L, idx);	\
				if (data == 0) return 0;	\
				lua_getmetatable(L, idx);	\
				lua_getglobal(L, "_mt_"#DATA);	\
				if (lua_rawequal(L, -1, -2)){	\
					lua_pop(L, 2);	\
					return *data;	\
																	}	\
				lua_pop(L, 2);	\
				return 0;	\
				}	\
			static void push_lua(lua_State* L, DATA* value){	\
				DATA** data = (DATA**)(lua_newuserdata(L, sizeof(DATA*)));	\
				*data = value;	\
				lua_getglobal(L, "_mt_"#DATA);	\
				assert(lua_istable(L, -1));	\
				lua_setmetatable(L, -2);	\
			}	\
		};	\

#endif