/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ModuleTalk.h"

#include "ModuleMsgTrigger.h"
#include "HotSwapServiceProxy.h"
#include "ModuleMgr.h"
#include "base.h"
#include "scmsg.h"

using namespace ff;

bool ModuleTalk::initialize(ff::ModuleMgr& mgr)
{
	ModuleMsgTrigger* pMsgTrigger = mgr.getModule<ModuleMsgTrigger>();
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleTalk, netMsg, cs_talk), false);

	return true;
}

void ModuleTalk::finalize()
{

}

static void broadCastMsg(Player& player, void* data)
{
	sc_talk* talk = (sc_talk*)data;
	player.send(*talk);
}

int ModuleTalk::netMsg(Player& player, const cs_talk& msg)
{
	sc_talk talk;
	talk.set_from(player.data().getBaseInfo().getName());
	talk.set_msg(msg.msg());

	HotSwapServiceProxy::instance().forEachPlayer(broadCastMsg, &talk);

	return 0;
}