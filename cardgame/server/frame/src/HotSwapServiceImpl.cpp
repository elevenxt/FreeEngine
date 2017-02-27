
#include "HotSwapServiceImpl.h"
#include "PlayerMgr.h"
#include "ComponentTick.h"
#include "ComponentRunnable.h"
#include "cfg_data_impl.h"

using namespace ff;

HotSwapServiceImpl::HotSwapServiceImpl()
{
	mModuleMgr.addComponentMgr<ComponentTickMgr>();
	mModuleMgr.addComponentMgr<ComponentRunnableMgr>();
}

Player* HotSwapServiceImpl::getPlayer(const char* playerid)
{
	return PlayerMgr::instance().getByPlayerId(playerid);
}

void HotSwapServiceImpl::forEachPlayer(ForEachPlayer cb, void* data)
{
	const std::map<std::string, PlayerImpl*>& allPlayers =
		PlayerMgr::instance().getAllLoginedPlayer();
	for (auto kv : allPlayers)
	{
		cb(*(kv.second), data);
	}
}

bool HotSwapServiceImpl::registerModule(const char* name, IModule* module)
{
	return mModuleMgr.registerModule(name, module) != nullptr;
}

IModule* HotSwapServiceImpl::getModule(const char* name)
{
	return mModuleMgr.getModule(name);
}

bool HotSwapServiceImpl::init()
{
	return mModuleMgr.initialize();
}

void HotSwapServiceImpl::uninit()
{
	mModuleMgr.finalize();
}

cfg_mgr& HotSwapServiceImpl::get_cfg_mgr()
{
	return cfg_mgr_impl::instance();
}