/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_SHOP_
#define _FF_MODULE_SHOP_

#include <map>
#include <string>
#include "Player.h"
#include "MsgMgr.h"
#include "IModule.h"
#include "csmsg.h"

namespace ff
{
	class ModuleShop : public IModule
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

	public:
		int netMsg(Player& player, const cs_buy_hero& msg);
		int netMsg(Player& player, const cs_shop_item& msg);
		int netMsg(Player& player, const cs_charge& msg);
	};
}

#endif
