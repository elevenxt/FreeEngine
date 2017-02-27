/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ModuleMgr.h"
#include "base.h"
#include "IModule.h"
#include "IComponentMgr.h"

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

IModule*	ModuleMgr::registerModule(std::string name, IModule* module)
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

	return module;
}

bool ModuleMgr::initialize()
{
	for (std::map<std::string, IModule*>::iterator iter = mModules.begin();
		iter != mModules.end(); ++iter)
	{
		if (!iter->second->initialize(*this))
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

	for (std::map<std::string, IModule*>::iterator iter = mModules.begin();
		iter != mModules.end(); ++iter)
	{
		iter->second->finalize();
		delete iter->second;
		SYSLOG_TRACE("module {} finalize over.", iter->first);
	}

	mModules.clear();
}

void ModuleMgr::preStartLoop()
{
	for (std::map<std::string, IModule*>::iterator iter = mModules.begin();
		iter != mModules.end(); ++iter)
	{
		iter->second->preStartLoop();
	}
}