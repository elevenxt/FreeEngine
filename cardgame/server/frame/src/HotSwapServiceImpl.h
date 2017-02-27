
/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_HOTSWAPSERVICEIMPL_
#define _FF_HOTSWAPSERVICEIMPL_

#include <map>
#include <string>

#include "HotSwapService.h"


namespace ff
{
	class HotSwapServiceImpl : public HotSwapService
	{
	public:
		HotSwapServiceImpl();
		virtual Player* getPlayer(const char* playerid);
		virtual void forEachPlayer(ForEachPlayer cb, void* data);
		virtual bool registerModule(const char* name, IModule* module);
		virtual IModule* getModule(const char* name);
		virtual bool init();
		virtual void uninit();
		virtual cfg_mgr& get_cfg_mgr();

	private:
		ModuleMgr mModuleMgr;
	};
}

#endif