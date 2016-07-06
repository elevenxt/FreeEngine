/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ModuleMgr.h"
#include "base.h"

using namespace ff;

void ModuleMgr::tick(int32_t delta)
{
	for (std::vector<IComponentMgr*>::iterator iter = mComponentMgrs.begin();
		iter != mComponentMgrs.end(); ++iter)
	{
		(*iter)->tick(delta);
	}
}

IModule*	ModuleMgr::getModule(std::string name)
{
	std::map<std::string, IModule*>::iterator iter = mModules.find(name);
	if (iter == mModules.end())
	{
		return nullptr;
	}

	return iter->second;
}

IModule*	ModuleMgr::registerModule(std::string name, IModule* module, int32_t order)
{
	if (mModules.find(name) != mModules.end() || module == nullptr)
	{
		return nullptr;
	}

	for (std::vector<IComponentMgr*>::iterator iter = mComponentMgrs.begin();
		iter != mComponentMgrs.end(); ++iter)
	{
		(*iter)->registerModule(name, module);
	}

	mModules[name] = module;
	mOrderModules.insert(std::make_pair(order, module));

	return module;
}

bool ModuleMgr::initialize()
{
	for (std::multimap<int32_t, IModule*>::iterator iter = mOrderModules.begin();
		iter != mOrderModules.end(); ++iter)
	{
		if (!iter->second->initialize())
		{
			SYSLOG_ERROR("module {} initialize failed.", iter->first);
			return false;
		}
		SYSLOG_TRACE("module {} initialize success.", iter->first);
	}

	for (std::vector<IComponentMgr*>::iterator iter = mComponentMgrs.begin();
		iter != mComponentMgrs.end(); ++iter)
	{
		(*iter)->initialize();
	}

	return true;
}

void ModuleMgr::finalize()
{
	for (std::vector<IComponentMgr*>::iterator iter = mComponentMgrs.begin();
		iter != mComponentMgrs.end(); ++iter)
	{
		(*iter)->finalize();
	}

	for (std::multimap<int32_t, IModule*>::reverse_iterator iter = mOrderModules.rbegin();
		iter != mOrderModules.rend(); ++iter)
	{
		iter->second->finalize();
		delete iter->second;
		SYSLOG_TRACE("module {} finalize over.", iter->first);
	}

	mOrderModules.clear();
	mModules.clear();
}

void ModuleMgr::preStartLoop()
{
	for (std::multimap<int32_t, IModule*>::iterator iter = mOrderModules.begin();
		iter != mOrderModules.end(); ++iter)
	{
		iter->second->preStartLoop();
	}
}