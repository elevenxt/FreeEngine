

#include "LuaState.h"

using namespace ff;

LuaState::LuaState(lua_State*	l)
{
	mL = l;
}

LuaState::~LuaState()
{
	if (mL != nullptr)
	{
		lua_close(mL);
	}
}

LuaState* LuaState::create(lua_State* L)
{
	lua_State* l = L;
	if (l == nullptr)
	{
		l = luaL_newstate();
		luaL_openlibs(l);
	}

	if (l == nullptr)
	{
		return nullptr;
	}

	LuaState* ls = new LuaState(l);
	if (ls == nullptr)
	{
		lua_close(l);
		return nullptr;
	}

	return ls;
}

void LuaState::free(LuaState* L)
{
	delete L;
}

bool LuaState::load(std::string initlua)
{
	SYS_VERIFY_RV(doFile(initlua), false);
	return true;
}

lua_State* LuaState::L()
{
	return mL;
}

bool LuaState::doFile(std::string file)
{
	if ((luaL_loadfile(mL, file.c_str()) || lua_pcall(mL, 0, LUA_MULTRET, 0)))
	{
		SYSLOG_ERROR(lua_tostring(mL, -1));
		return false;
	}

	return true;
}

void LuaState::reset()
{
	if (mL != nullptr)
	{
		lua_close(mL);
	}

	mL = luaL_newstate();
	luaL_openlibs(mL);
}

void LuaState::pushTable(std::vector<std::string> tables)
{
	
}