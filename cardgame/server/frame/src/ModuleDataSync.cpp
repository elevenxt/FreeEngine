
#include "ModuleDataSync.h"
#include "base.h"
#include "ModuleMgr.h"
#include "ConstString.h"
#include "PlayerMgr.h"
#include "scmsg.h"

using namespace ff;

bool ModuleDataSync::initialize(ModuleMgr& mgr)
{
	mModuleRocksDb = mgr.getModule<ModuleRocksDb>();
	SYS_VERIFY_RV(mModuleRocksDb != nullptr, false);

	return true;
}

void ModuleDataSync::finalize()
{

}

int64_t ModuleDataSync::loopTick(int64_t delta)
{
	saveDirtyData();
	return 10000;
}

bool ModuleDataSync::syncData(Player& player)
{
	PlayerImpl& pimpl = dynamic_cast<PlayerImpl&>(player);
	PlayerDataProto pdp;
	pimpl.dataImpl().toProto(&pdp, false, true, true);

	sc_player_data spd;
	spd.set_data(pdp.SerializeAsString());
	return player.send(spd);
}

void ModuleDataSync::syncDirtyData()
{
	std::vector<PlayerImpl*> pi = PlayerMgr::instance().getSyncDirtyPlayer();
	for (PlayerImpl* pimpl : pi)
	{
		PlayerDataProto pdp;
		pimpl->dataImpl().toProto(&pdp, false, true);

		sc_player_data spd;
		spd.set_data(pdp.SerializeAsString());
		((Player*)pimpl)->send(spd);		
	}
	PlayerMgr::instance().clearDirty(IMarkDirty::SYNC_DIRTY);
}

void ModuleDataSync::saveDirtyData()
{
	std::vector<PlayerImpl*> pi = PlayerMgr::instance().getDbDirtyPlayer();
	for (PlayerImpl* pimpl : pi)
	{
		savePlayerData(*pimpl);		
	}
	PlayerMgr::instance().clearDirty(IMarkDirty::DB_DIRTY);
}

int32_t ModuleDataSync::savePlayerData(PlayerImpl& player)
{
	if (!player.dataImpl().isDirty(IMarkDirty::DB_DIRTY)) 
	{
		return 0;
	}
	player.dataImpl().clearDirty(IMarkDirty::DB_DIRTY);

	PlayerDataProto pdp;
	player.dataImpl().toProto(&pdp, true, false);
	std::string pid = player.data().getBaseInfo().getId();
	mModuleRocksDb->save(fmt::format("{}_{}", CS::DBTAB_PLAYER, pid)
		, pdp.SerializeAsString());

	return 0;
}