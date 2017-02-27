
/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_HOTSWAPSERVICE_
#define _FF_HOTSWAPSERVICE_

#include "IModule.h"
#include "Player.h"
#include "ModuleMgr.h"
#include "cfg_data.h"

namespace ff
{
	typedef void(*ForEachPlayer)(Player&,void*);
	
	class HotSwapService
	{
	public:
		virtual ~HotSwapService() { };
		virtual Player* getPlayer(const char* playerid) = 0;
		virtual void forEachPlayer(ForEachPlayer cb, void* data) = 0;
		virtual bool registerModule(const char* name, IModule* module) = 0;
		virtual IModule* getModule(const char* name) = 0;
		virtual bool init() = 0;
		virtual void uninit() = 0;
		virtual cfg_mgr& get_cfg_mgr() = 0;
	};
}

#endif