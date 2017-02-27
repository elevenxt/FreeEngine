/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#include <functional>
#include "ModulePackHero.h"

#include "ModuleMsgTrigger.h"

#include "ModuleMgr.h"
#include "base.h"

using namespace ff;

bool ModulePackHero::initialize(ff::ModuleMgr& mgr)
{
	ModuleMsgTrigger* pMsgTrigger = mgr.getModule<ModuleMsgTrigger>();
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModulePackHero, netMsg, cs_pack_hero), false);
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModulePackHero, netMsg, cs_select_teammember), false);

	return true;
}

void ModulePackHero::finalize()
{

}

int ModulePackHero::netMsg(Player& player, const cs_pack_hero& msg)
{
	switch (msg.action())
	{
		// ≥ˆ €”¢–€
	case 1:
	{
		int slot = msg.slot();
		Card& card = player.data().getPackage().getSlot(slot);
		if (card.getId() <= 0)
		{
			return -1;
		}
		card.setId(-1);
		int oldGold = player.data().getBaseInfo().getGold();
		player.data().getBaseInfo().setGold(oldGold + 10000);
	}
		break;
		// …˝º∂”¢–€
	case 2:
		int slot = msg.slot();
		Card& card = player.data().getPackage().getSlot(slot);
		if (card.getId() <= 0)
		{
			return -1;
		}
		card.setLevel(card.getLevel() + 1);
		break;
	}
	return 0;
}

int32_t ModulePackHero::netMsg(Player& player, const cs_select_teammember& msg)
{
	Card& teamCard = player.data().getTeamInfo().getTeamMember(msg.teamslot());
	Card& packCard = player.data().getPackage().getSlot(msg.packslot());

	int32_t id = teamCard.getId();
	int32_t skill = teamCard.getLeaderSkill();
	int32_t level = teamCard.getLevel();

	teamCard.setId(packCard.getId());
	teamCard.setLeaderSkill(packCard.getLeaderSkill());
	teamCard.setLevel(packCard.getLevel());

	packCard.setId(id);
	packCard.setLeaderSkill(skill);
	packCard.setLevel(level);

	return 0;
}
