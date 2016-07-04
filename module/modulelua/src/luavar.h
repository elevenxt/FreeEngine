/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _UTS_LUAVAR_
#define _UTS_LUAVAR_

#include "lua.hpp"

namespace ff
{
	class LuaVar
	{
	public:
		static void pushVarMt(lua_State* L);
	};
}

#endif