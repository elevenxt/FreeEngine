/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleNetService.h"
#include "base.h"

using namespace ff;

bool ModuleNetService::initialize(ff::ModuleMgr& mgr)
{

	return true;
}

void ModuleNetService::finalize()
{

}

NetService* ModuleNetService::getService(const std::string& name)
{
	std::map<std::string, NetService*>::iterator iter = mServices.find(name);
	if (iter == mServices.end())
	{
		NetService* service = new NetService();
		mServices[name] = service;
		return service;
	}

	return iter->second;
}

int64_t ModuleNetService::loopTick(int64_t delta)
{
	for (std::map<std::string, NetService*>::iterator iter = mServices.begin();
		iter != mServices.end(); ++iter)
	{
		iter->second->poolOnce(128, 0);
	}
	return 1;
}