
#include "base.h"
#include "LuaMachine.h"
#include "StringUtil.h"

using namespace ff;

LuaMachine::LuaMachine()
{
	mL = nullptr;
}

LuaMachine::~LuaMachine()
{
	if (mL != nullptr)
	{
		lua_close(mL);
		mL = nullptr;
	}
}

LuaMachine* LuaMachine::create()
{
	return new LuaMachine();
}

bool LuaMachine::init()
{
	return true;
}

bool LuaMachine::switchLuaState(lua_State* L)
{	
	SYS_VERIFY_RV(L != nullptr, false);
	if (mL != nullptr)
	{
		lua_close(mL);
	}

	mL = L;

	return true;
}

void LuaMachine::uninit()
{

}

bool LuaMachine::tick(int64_t delta)
{
	return true;
}

lua_State* LuaMachine::getLuaState()
{
	return mL;
}