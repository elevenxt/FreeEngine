/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_PLAYER_MGR_
#define _FF_PLAYER_MGR_
#include <cinttypes>
#include <map>
#include <string>
#include <vector>

#include "PlayerImpl.h"
#include "Singleton.h"
#include "MarkDirtyMap.h"

namespace ff
{
	class PlayerMgr : public Singleton<PlayerMgr>, public MarkDirtyMap
	{
	public:
		PlayerMgr();

		PlayerImpl* createPlayer(NetService* netService, int32_t netid);
		void		deletePlayer(PlayerImpl* player);

		PlayerImpl* bindUserId(Player& player);

		PlayerImpl* getByPlayerId(std::string playerid);
		PlayerImpl* getByNetId(int32_t netid);
		const std::map<std::string, PlayerImpl*>& getAllLoginedPlayer();

		bool isPlayerDbDirty(PlayerImpl& player);

		std::vector<PlayerImpl*> getDbDirtyPlayer();
		std::vector<PlayerImpl*> getSyncDirtyPlayer();

	private:
		void extendSlot(int32_t tonum);
		void markPlayer(PlayerImpl* player);
		void unmarkPlayer(PlayerImpl* player);

	private:
		std::map<int32_t, PlayerImpl*>	mMapNetPlayer;
		std::map<std::string, PlayerImpl*>	mMapPlayer;

		std::vector<int32_t> mFreeId;
		std::vector<PlayerImpl*>	mPlayerSlot;
	};
}

#endif