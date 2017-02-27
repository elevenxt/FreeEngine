/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#include <functional>

#include "ModuleMgr.h"
#include "ModuleMsgTrigger.h"
#include "base.h"

using namespace ff;

bool ModuleMsgTrigger::initialize(ff::ModuleMgr& mgr)
{
	return true;
}

void ModuleMsgTrigger::finalize()
{

}

int32_t ModuleMsgTrigger::triggerNetMsg(Player& player, int32_t msgid, const char* msg, int32_t len)
{
	return mMsgMgr.triggerMsg(player, msgid, msg, len);
}