/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_BATTLE_
#define _FF_MODULE_BATTLE_
#include <cinttypes>
#include <map>
#include <string>
#include "Player.h"
#include "MsgMgr.h"
#include "IModule.h"
#include "csmsg.h"
#include "BattleLogic.h"

namespace ff
{
	class ModuleBattle : public IModule
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

	public:
		int32_t netMsg(Player& player, const cs_challenge_mission& msg);

	private:
		std::vector<BattleLogic::Character> getMissionCharacter(int32_t type, int32_t level);
		std::vector<BattleLogic::Character> getCharacter(std::vector<int32_t> heros);
	};


}

#endif
