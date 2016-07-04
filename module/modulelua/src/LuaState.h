/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_LUASTATE
#define _US_LUASTATE

#include <string>
#include <vector>

#include "LuaTypeConvert.h"
#include "lua.hpp"
#include "base.h"

namespace ff
{
	class LuaState
	{
	private:
		LuaState(lua_State*	l);
		~LuaState();

		LuaState(const LuaState&) = delete;
		void operator=(const LuaState&) = delete;
		
	public:
		static LuaState* create(lua_State* L=0);
		static void free(LuaState* L);

		lua_State* L();

		bool load(std::string initlua);

		bool doFile(std::string file);
		void reset();

		template<typename T>
		int push_lua(lua_State* l, T t)
		{
			LuaTypeConvert<T>::push_lua(l, t);
			return 1;
		}

		template<typename RV, typename ...ARGS>
		typename std::enable_if<std::is_same<RV, void>::value, RV>::type
			call(const std::string& tab, const std::string& func, ARGS... args)
		{
			int32_t ctop = lua_gettop(mL);
			lua_getglobal(mL, "_G_EXCEPTION_INFO");
			SYS_VERIFY_G(lua_isfunction(mL, -1));

			lua_getglobal(mL, tab.c_str());
			SYS_VERIFY_G(lua_istable(mL, -1));

			lua_getfield(mL, -1, func.c_str());
			SYS_VERIFY_G(lua_isfunction(mL, -1));
			{
				int res[] = { 0, push_lua(mL, args)... }; (void)res;
				if (0 != lua_pcall(mL, (int32_t)sizeof...(ARGS), 1, -3 - (int32_t)sizeof...(ARGS)))
				{
					const char* err = lua_tostring(mL, -1);
					if (err == nullptr)
					{
						err = "unknown error";
					}
					SYSLOG_ERROR(err);
				}
			}

		FAIL:
			lua_settop(mL, ctop);
		}

		template<typename RV, typename ...ARGS>
		typename std::enable_if<!std::is_same<RV, void>::value, RV>::type
			call(const std::string& tab, const std::string& func, ARGS... args)

		{
			int32_t ctop = lua_gettop(mL);

			lua_getglobal(mL, "_G_EXCEPTION_INFO");
			SYS_VERIFY_G(lua_isfunction(mL, -1));

			lua_getglobal(mL, tab.c_str());
			SYS_VERIFY_G(lua_istable(mL, -1));

			lua_getfield(mL, -1, func.c_str());
			SYS_VERIFY_G(lua_isfunction(mL, -1));

			{
				int res[] = { 0, push_lua(mL, args)... }; (void)res;
				if (0 != lua_pcall(mL, (int32_t)sizeof...(ARGS), 1, -3 - (int32_t)sizeof...(ARGS)))
				{
					const char* err = lua_tostring(mL, -1);
					if (err == nullptr)
					{
						err = "unknown error";
					}
					SYSLOG_ERROR(err);
					return RV();
				}

				RV rv = LuaTypeConvert<RV>::from_lua(mL, -1);
				lua_settop(mL, ctop);
				return rv;
			}

		FAIL:
			lua_settop(mL, ctop);
			return RV();
		}

		void pushTable(std::vector<std::string> tables);

	private:
		lua_State*	mL;
	};
}

#endif