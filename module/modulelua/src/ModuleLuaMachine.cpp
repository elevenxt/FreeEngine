#include "ModuleLuaMachine.h"
#include "LuaMachine.h"
#include "LuaExportFuncs.h"

using namespace ff;


bool ModuleLuaMachine::initialize(ModuleMgr& mgr)
{
	return true;
}

void ModuleLuaMachine::finalize()
{
	LuaMachine::instance().uninit();
}

void ModuleLuaMachine::preStartLoop()
{
	SYS_VERIFY_R(reloadLuaMachine());
	SYS_VERIFY_R(LuaMachine::instance().init());
}

bool ModuleLuaMachine::initLuaMachine(std::string entry)
{
	mEntry = entry;	
	return true;
}

int64_t ModuleLuaMachine::loopTick(int64_t delta)
{
	LuaMachine::instance().tick(delta);

	// 测试,20秒重新热加载lua虚拟机
/*
	static int64_t hots = 20000;
	hots -= delta;
	if (hots<0)
	{
		hots = 20000;
		reloadLuaMachine();
	}
*/
	return 1;
}

bool ModuleLuaMachine::reloadLuaMachine()
{
	lua_State* L = luaL_newstate();
	// 加载c扩展库
	SYS_VERIFY_RV(L != nullptr, false);
	LuaExportFuncs::instance().bindLua(L);

	// 初始化脚本
	if (0 != luaL_dofile(L, mEntry.c_str()))
	{
		SYSLOG_ERROR(lua_tostring(L, -1));
		return false;
	}

	SYS_VERIFY_RV(LuaMachine::instance().switchLuaState(L), false);
	
	return true;
}