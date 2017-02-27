

#include "PlayerMgr.h"

using namespace ff;

PlayerMgr::PlayerMgr()
{
	extendSlot(1024);
}

PlayerImpl* PlayerMgr::createPlayer(NetService* netService, int32_t netid)
{
	if (mMapNetPlayer.find(netid) != mMapNetPlayer.end())
	{
		return nullptr;
	}

	PlayerImpl* pd = new PlayerImpl(netService, netid);
	markPlayer(pd);
	mMapNetPlayer[netid] = pd;
	return pd;
}

PlayerImpl* PlayerMgr::bindUserId(Player& player)
{
	PlayerImpl* pImpl = dynamic_cast<PlayerImpl*>(&player);

	std::string pid = player.data().getBaseInfo().getId();
	std::map<std::string, PlayerImpl*>::iterator dupPlayer = mMapPlayer.find(pid);
	if (dupPlayer != mMapPlayer.end())
	{
		return dupPlayer->second;
	}

	mMapPlayer[pid] = pImpl;
	return nullptr;
}

PlayerImpl* PlayerMgr::getByPlayerId(std::string playerid)
{
	std::map<std::string, PlayerImpl*>::iterator iter = mMapPlayer.find(playerid);
	if (iter == mMapPlayer.end())
	{
		return nullptr;
	}

	return iter->second;
}

PlayerImpl* PlayerMgr::getByNetId(int32_t netid)
{
	std::map<int32_t, PlayerImpl*>::iterator iter = mMapNetPlayer.find(netid);
	if (iter == mMapNetPlayer.end())
	{
		return nullptr;
	}

	return iter->second;
}

const std::map<std::string, PlayerImpl*>& PlayerMgr::getAllLoginedPlayer()
{
	return mMapPlayer;
}

void PlayerMgr::deletePlayer(PlayerImpl* player)
{
	mMapNetPlayer.erase(player->getNetId());
	std::string pid = player->data().getBaseInfo().getId();
	mMapPlayer.erase(pid);
	unmarkPlayer(player);

	delete player;
}

void PlayerMgr::extendSlot(int32_t tonum)
{
	int oldSize = mPlayerSlot.size();
	if (tonum <= oldSize)
	{
		// ²»ÔÊÐíËõÐ¡
		return;
	}
	
	mPlayerSlot.resize(tonum, nullptr);
	for (int32_t i = oldSize; i < tonum; i++)
	{
		mFreeId.push_back(i);
	}
}

void PlayerMgr::markPlayer(PlayerImpl* player)
{	
	if (mFreeId.empty())
	{
		extendSlot(mPlayerSlot.size() + 1024);
	}
	int32_t nFreeSlot = mFreeId.back();
	mFreeId.pop_back();

	mPlayerSlot[nFreeSlot] = player;
	player->dataImpl().init(this, nFreeSlot
		, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
}

void PlayerMgr::unmarkPlayer(PlayerImpl* player)
{
	int32_t nSlot = player->dataImpl().getIdxInParent();
	mPlayerSlot[nSlot] = nullptr;
	mFreeId.push_back(nSlot);
	removeChild(nSlot);
}

bool PlayerMgr::isPlayerDbDirty(PlayerImpl& player)
{
	int32_t idx = player.dataImpl().getIdxInParent();
	return isDirty(idx, IMarkDirty::DB_DIRTY);
}

std::vector<PlayerImpl*> PlayerMgr::getDbDirtyPlayer()
{
	std::vector<PlayerImpl*> dp;
	std::vector<int32_t> dc = getAllDirtyChild(IMarkDirty::DB_DIRTY);
	for (int32_t di : dc)
	{
		if (mPlayerSlot[di] == nullptr)
		{
			continue;
		}
		dp.push_back(mPlayerSlot[di]);
	}

	return dp;
}

std::vector<PlayerImpl*> PlayerMgr::getSyncDirtyPlayer()
{
	std::vector<PlayerImpl*> dp;
	std::vector<int32_t> dc = getAllDirtyChild(IMarkDirty::SYNC_DIRTY);
	for (int32_t di : dc)
	{
		if (mPlayerSlot[di] == nullptr)
		{
			continue;
		}
		dp.push_back(mPlayerSlot[di]);
	}

	return dp;
}