/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _UTS_LUA_MACHINE_
#define _UTS_LUA_MACHINE_

#include <string>
#include "Singleton.h"
#include "lua.hpp"

namespace ff
{
	class LuaMachine : public Singleton<LuaMachine>
	{
	public:
		LuaMachine();

	public:
		static const char* sLuaGlobalDataName;

		~LuaMachine();
		static LuaMachine* create();

		bool init();
		bool switchLuaState(lua_State* L);
		void uninit();
		bool tick(int64_t delta);

		lua_State* getLuaState();

	private:
		lua_State*		mL;
	};
}
#endif