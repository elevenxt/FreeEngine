/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_NETSERVICE_
#define _US_MODULE_NETSERVICE_

#include <string>
#include <vector>
#include <map>

#include "ut_net_listener.h"
#include "IModule.h"
#include "ComponentTick.h"
#include "NetService.h"
#include "NetAddress.h"

namespace ff
{
	class ModuleNetService : public IModule, public ComponentTick
	{
	public:
		virtual bool initialize(ff::ModuleMgr& mgr);
		virtual	void finalize();

		NetService* getService(const std::string& name);

	private:
		virtual int64_t loopTick(int64_t delta);

	private:
		std::map<std::string, NetService*>	mServices;
	};
}

#endif
