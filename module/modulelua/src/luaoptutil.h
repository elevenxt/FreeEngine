/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _UTS_LUAOPTUTIL_
#define _UTS_LUAOPTUTIL_

#include "lua.hpp"
#include <map>
#include <string>
#include <vector>


void	lualibs_open(lua_State* L, const luaL_Reg* lib);

int		invalid_newindex(lua_State* L);
// 把栈顶数据设置到全局表中
int		lua_set_global(lua_State *L, const char* tablse);
// 获取全局表中的数据，放到栈顶
int		lua_get_global(lua_State *L, const char* tablse);

int		lua_set_table(lua_State* L, const std::map<std::string, std::string>& vals);

#endif