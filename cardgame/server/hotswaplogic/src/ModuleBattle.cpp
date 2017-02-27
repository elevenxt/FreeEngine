/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#include <functional>
#include "ModuleBattle.h"

#include "ModuleMsgTrigger.h"
#include "HotSwapServiceProxy.h"
#include "ModuleMgr.h"
#include "base.h"
#include "scmsg.h"

using namespace ff;

bool ModuleBattle::initialize(ff::ModuleMgr& mgr)
{
	ModuleMsgTrigger* pMsgTrigger = mgr.getModule<ModuleMsgTrigger>();
	SYS_VERIFY_RV(REG_NETMSG(pMsgTrigger, ModuleBattle, netMsg, cs_challenge_mission), false);

	return true;
}

void ModuleBattle::finalize()
{

}

int ModuleBattle::netMsg(Player& player, const cs_challenge_mission& msg)
{
	switch (msg.type())
	{
	case 1:
		if (msg.level() > player.data().getBaseInfo().getMainLine()+1)
		{
			return -1;
		}
		break;
	case 2:
		if (msg.level() > player.data().getBaseInfo().getEliteLine() + 1)
		{
			return -1;
		}
		break;
	case 3:
		if (msg.level() > player.data().getBaseInfo().getHeroLine() + 1)
		{
			return -1;
		}
		break;
	}
	cfg_mgr& cfgMgr = HotSwapServiceProxy::instance().get_cfg_mgr();

	std::vector<BattleLogic::Character> lChar;
	std::vector<BattleLogic::Character> rChar = getMissionCharacter(msg.type(), msg.level());
	TeamInfo& team = player.data().getTeamInfo();
	for (int32_t i=0; i<team.sizeTeamMember(); i++)
	{
		Card& card = team.getTeamMember(i);
		if (card.getId() <= 0)
		{
			continue;
		}

		cfg_heros::data* cfg = cfgMgr.get_cfg_heros().get(card.getId());
		if (cfg == nullptr)
		{
			continue;
		}

		BattleLogic::Character character;
		character.pos = i;
		character.atk = cfg->get_atk();
		character.hp = cfg->get_hp();
		character.id = card.getId();
		lChar.push_back(character);
	}

	std::vector<BattleLogic::Action> report;
	bool win = BattleLogic::makeBattleReport(report, lChar, rChar);
	if (win)
	{
		switch (msg.type())
		{
		case 1:
			if (msg.level() > player.data().getBaseInfo().getMainLine())
			{
				player.data().getBaseInfo().setMainLine(msg.level());
			}
			break;
		case 2:
			if (msg.level() > player.data().getBaseInfo().getEliteLine())
			{
				player.data().getBaseInfo().setEliteLine(msg.level());
			}
			break;
		case 3:
			if (msg.level() > player.data().getBaseInfo().getHeroLine())
			{
				player.data().getBaseInfo().setHeroLine(msg.level());
			}
			break;
		}
	}

	sc_battle_report response;
	for (int32_t i=0; i<6; i++)
	{
		response.add_lchar(0);
		response.add_rchar(0);
	}
	for (BattleLogic::Character c : lChar)
	{
		response.set_lchar(c.pos, c.id);
	}

	for (BattleLogic::Character c : rChar)
	{
		response.set_rchar(c.pos, c.id);
	}

	for (BattleLogic::Action act : report)
	{
		sc_battle_action* scact = response.add_actions();
		scact->set_act(act.act);
		scact->set_from(act.from);
		scact->set_to(act.to);
		scact->set_value(act.value);
	}

	if (!player.send(response)) 
	{
		return -1;
	}

	return 0;
}

std::vector<BattleLogic::Character> ModuleBattle::getMissionCharacter(int32_t type, int32_t level)
{
	std::vector<BattleLogic::Character> chars;
	std::vector<int32_t> heroids;

	cfg_mgr& cfgMgr = HotSwapServiceProxy::instance().get_cfg_mgr();
	switch (type)
	{
	case 1:
	{
		cfg_misnormal::data* cfg = cfgMgr.get_cfg_misnormal().get(level);
		if (cfg == nullptr)
		{
			return chars;
		}
		heroids.push_back(cfg->get_heros1());
		heroids.push_back(cfg->get_heros2());
		heroids.push_back(cfg->get_heros3());
		heroids.push_back(cfg->get_heros4());
		heroids.push_back(cfg->get_heros5());
		heroids.push_back(cfg->get_heros6());
	}
		break;
	case 2:
	{
		cfg_miselite::data* cfg = cfgMgr.get_cfg_miselite().get(level);
		if (cfg == nullptr)
		{
			return chars;
		}
		heroids.push_back(cfg->get_heros1());
		heroids.push_back(cfg->get_heros2());
		heroids.push_back(cfg->get_heros3());
		heroids.push_back(cfg->get_heros4());
		heroids.push_back(cfg->get_heros5());
		heroids.push_back(cfg->get_heros6());
	}
		break;
	case 3:
	{
		cfg_mishero::data* cfg = cfgMgr.get_cfg_mishero().get(level);
		if (cfg == nullptr)
		{
			return chars;
		}
		heroids.push_back(cfg->get_heros1());
		heroids.push_back(cfg->get_heros2());
		heroids.push_back(cfg->get_heros3());
		heroids.push_back(cfg->get_heros4());
		heroids.push_back(cfg->get_heros5());
		heroids.push_back(cfg->get_heros6());
	}
		break;
	}

	return getCharacter(heroids);
}

std::vector<BattleLogic::Character> ModuleBattle::getCharacter(std::vector<int32_t> heros)
{
	std::vector<BattleLogic::Character> chars;
	cfg_mgr& cfgMgr = HotSwapServiceProxy::instance().get_cfg_mgr();
	for (int32_t i=0; i<(int32_t)heros.size(); i++)
	{
		if (heros[i] <= 0)
		{
			continue;
		}
		cfg_heros::data* cfg = cfgMgr.get_cfg_heros().get(heros[i]);

		BattleLogic::Character character;
		character.pos = i;
		character.atk = cfg->get_atk();
		character.hp = cfg->get_hp();
		character.id = heros[i];
		chars.push_back(character);
	}
	return chars;
}