
#include <cinttypes>

#include "luaoptutil.h"
#include "StringUtil.h"


void lualibs_open(lua_State* L, const luaL_Reg* lib)
{
	for (; lib->name != NULL; lib++)
	{  /* fill the table with given functions */
		lua_pushcclosure(L, lib->func, 0);  /* closure with those upvalues */
		lua_setfield(L, -2, lib->name);
	}
}

int32_t invalid_newindex(lua_State* L)
{
	lua_pushstring(L, "new index error");
	lua_error(L);
	return 0;
}

int32_t lua_set_global(lua_State *L, const char* tablse)
{
	int32_t ctop = lua_gettop(L) - 1;
	std::vector<std::string> tables = ff::StringUtil::split(tablse, ".");
	lua_getglobal(L, tables[0].c_str());
	if (!lua_istable(L, -1) && !lua_isnil(L, -1))
	{
		lua_settop(L, ctop);
		return -1;
	}

	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushstring(L, "__newindex");
		lua_pushcfunction(L, invalid_newindex);
		lua_rawset(L, -3);

		lua_pushvalue(L, -1);
		lua_setglobal(L, tables[0].c_str());
	}

	for (int32_t i = 1; i < (int32_t)tables.size() - 1; i++)
	{
		lua_getfield(L, -1, tables[i].c_str());
		if (!lua_istable(L, -1) && !lua_isnil(L, -1))
		{
			lua_settop(L, ctop);
			return -1;
		}

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			lua_newtable(L);
			lua_pushstring(L, "__newindex");
			lua_pushcfunction(L, invalid_newindex);
			lua_rawset(L, -3);

			lua_pushvalue(L, -1);
			lua_setfield(L, -3, tables[i].c_str());
		}
	}
	lua_pushvalue(L, ctop+1);
	lua_setfield(L, -2, tables.back().c_str());

	lua_settop(L, ctop);
	return 0;
}

int32_t lua_get_global(lua_State *L, const char* table)
{
	int32_t ctop = lua_gettop(L);

	std::vector<std::string> tables = ff::StringUtil::split(table, ".");
	lua_getglobal(L, tables[0].c_str());

	if (tables.size() == 1)
	{
		return 0;
	}

	if (!lua_istable(L, -1))
	{		
		lua_settop(L, ctop);
		lua_pushnil(L);
		return -1;
	}

	for (int32_t i = 1; i < (int32_t)tables.size(); i++)
	{
		lua_getfield(L, -1, tables[i].c_str());
		if (i == (int32_t)tables.size() -1)
		{
			lua_replace(L, ctop + 1);
			lua_settop(L, ctop + 1);
			return 0;
		}

		if (!lua_istable(L, -1))
		{
			lua_settop(L, ctop);
			lua_pushnil(L);
			return -1;
		}
	}

	return 0;
}

int32_t lua_set_table(lua_State* L, const std::map<std::string, std::string>& vals)
{
	for (std::map<std::string, std::string>::const_iterator iter = vals.begin();
		iter != vals.end(); ++iter)
	{
		lua_pushstring(L, iter->first.c_str());
		lua_pushstring(L, iter->second.c_str());
		lua_rawset(L, -3);
	}
	return 0;
}