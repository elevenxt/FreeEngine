
#include "HotSwapServiceProxy.h"

using namespace ff;

void HotSwapServiceProxy::reset(HotSwapService* service)
{
	mService = service;
}

bool HotSwapServiceProxy::init()
{
	return mService->init();
}

void HotSwapServiceProxy::uninit()
{
	mService->uninit();
}

Player* HotSwapServiceProxy::getPlayer(const char* playerid)
{
	return mService->getPlayer(playerid);
}

void HotSwapServiceProxy::forEachPlayer(ForEachPlayer cb, void* data)
{
	return mService->forEachPlayer(cb, data);
}

bool HotSwapServiceProxy::registerModule(const char* name, ff::IModule* module)
{
	return mService->registerModule(name, module);
}

ff::IModule* HotSwapServiceProxy::getModule(const char* name)
{
	return mService->getModule(name);
}

cfg_mgr& HotSwapServiceProxy::get_cfg_mgr()
{
	return mService->get_cfg_mgr();
}
