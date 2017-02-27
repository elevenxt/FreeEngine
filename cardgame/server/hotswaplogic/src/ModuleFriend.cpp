/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ModuleFriend.h"

#include "ModuleMsgTrigger.h"
#include "HotSwapServiceProxy.h"
#include "ModuleMgr.h"
#include "base.h"
#include "scmsg.h"

using namespace ff;

bool ModuleFriend::initialize(ff::ModuleMgr& mgr)
{
	ModuleMsgTrigger* pMsgTrigger = mgr.getModule<ModuleMsgTrigger>();
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleFriend, netMsg, cs_friend_add), false);
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleFriend, netMsg, cs_friend_mobility), false);

	return true;
}

void ModuleFriend::finalize()
{

}

int ModuleFriend::netMsg(Player& player, const cs_friend_add& msg)
{
	Player* pf = HotSwapServiceProxy::instance().getPlayer(msg.name().c_str());
	// 目前只支持添加在线玩家,单向添加
	if (pf == nullptr)
	{
		return 0;
	}

	for (int32_t i = 0; i < player.data().sizeFriends(); i++)
	{
		FriendInfo& fr = player.data().getFriends(i);
		if (std::string(fr.getInfo().getId()).empty())
		{
			fr.getInfo().setId(pf->data().getBaseInfo().getId());
			fr.getInfo().setName(pf->data().getBaseInfo().getName());
			fr.getInfo().setLevel(pf->data().getBaseInfo().getLevel());
			break;
		}
	}
	return 0;
}

int ModuleFriend::netMsg(Player& player, const cs_friend_mobility& msg)
{
	FriendInfo& fr = player.data().getFriends(msg.idx());
	// 目前只支持在线互动
	switch (msg.action())
	{
		// 给体力
	case 1:
	{
		Player* pf = HotSwapServiceProxy::instance().getPlayer(fr.getInfo().getId());
		if (pf == nullptr)
		{
			return 0;
		}
		for (int32_t i=0; i<pf->data().sizeFriends(); i++)
		{
			if (std::string(pf->data().getFriends(i).getInfo().getId()) 
				== std::string(player.data().getBaseInfo().getId()))
			{
				pf->data().getFriends(i).setMobility(5);
				break;
			}
		}
	}
		break;
		// 领体力
	case 2:
		int mb = player.data().getBaseInfo().getMobility();
		player.data().getBaseInfo().setMobility(mb + fr.getMobility());
		fr.setMobility(0);
		break;
	}
	return 0;
}