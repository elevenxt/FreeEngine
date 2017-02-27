/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#include <cinttypes>
#include <functional>
#include "ModuleShop.h"

#include "ModuleMsgTrigger.h"

#include "ModuleMgr.h"
#include "base.h"

using namespace ff;

bool ModuleShop::initialize(ff::ModuleMgr& mgr)
{
	ModuleMsgTrigger* pMsgTrigger = mgr.getModule<ModuleMsgTrigger>();
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleShop, netMsg, cs_buy_hero), false);
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleShop, netMsg, cs_shop_item), false);
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleShop, netMsg, cs_charge), false);

	return true;
}

void ModuleShop::finalize()
{

}

int32_t ModuleShop::netMsg(Player& player, const cs_buy_hero& msg)
{
	int32_t oldDiamond = player.data().getBaseInfo().getDiamond();
	switch (msg.idx())
	{
	case 1:
	{
		int32_t findSlot = -1;
		Package& package = player.data().getPackage();
		for (int32_t i = 0; i < package.sizeSlot(); i++)
		{
			if (package.getSlot(i).getId() <= 0)
			{
				findSlot = i;
				break;
			}
		}
		if (findSlot < 0)
		{
			// 包裹已满
			return -1;
		}
		player.data().getPackage().getSlot(0);
		if (oldDiamond < 100)
		{
			return 0;
		}
		player.data().getBaseInfo().setDiamond(oldDiamond - 100);
		Card& hero = package.getSlot(findSlot);
		hero.setLevel(1);
		hero.setId(rand()%500+1);
	}
	break;
	case 2:
	{
		std::vector<int32_t> findSlot;
		Package& package = player.data().getPackage();
		for (int32_t i = 0; i < package.sizeSlot(); i++)
		{
			if (package.getSlot(i).getId() <= 0)
			{
				findSlot.push_back(i);
				if (findSlot.size() >= 10)
				{
					break;
				}
			}
		}
		if (findSlot.size() < 10)
		{
			// 包裹已满
			return -1;
		}

		if (oldDiamond < 1000)
		{
			return 0;
		}
		player.data().getBaseInfo().setDiamond(oldDiamond - 1000);

		for (int slot : findSlot)
		{
			Card& hero = package.getSlot(slot);
			hero.setLevel(1);
			hero.setId(rand() % 500 + 1);
		}
	}
	break;
	}

	return 0;
}

int ModuleShop::netMsg(Player& player, const cs_shop_item& msg)
{
	int oldDiamond = player.data().getBaseInfo().getDiamond();
	switch (msg.idx())
	{
	case 1:
	{
		if (oldDiamond < 100)
		{
			return 0;
		}
		player.data().getBaseInfo().setDiamond(oldDiamond - 100);
		int oldGold = player.data().getBaseInfo().getGold();
		player.data().getBaseInfo().setGold(oldGold+10000);
	}
	break;
	case 2:
	{
		if (oldDiamond < 200)
		{
			return 0;
		}
		player.data().getBaseInfo().setDiamond(oldDiamond - 200);
		int32_t oldVal = player.data().getBaseInfo().getMobility();
		player.data().getBaseInfo().setMobility(oldVal + 100);
	}
	break;
	case 3:
	{
		if (oldDiamond < 300)
		{
			return 0;
		}
		player.data().getBaseInfo().setDiamond(oldDiamond - 300);
	}
		break;
	}	

	return 0;
}

int ModuleShop::netMsg(Player& player, const cs_charge& msg)
{
	int32_t oldDiamond = player.data().getBaseInfo().getDiamond();
	player.data().getBaseInfo().setDiamond(oldDiamond + msg.diamond());

	return 0;
}