
/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_HOTSWAPSERVICE_PROXY_
#define _FF_HOTSWAPSERVICE_PROXY_

#include "Singleton.h"
#include "HotSwapService.h"

namespace ff
{
	class HotSwapServiceProxy : public HotSwapService, public Singleton<HotSwapServiceProxy>
	{
	private:
		friend class CardGameLogicPlugin;
		void reset(HotSwapService* service);
		virtual bool init();
		virtual void uninit();

	public:
		virtual Player* getPlayer(const char* playerid);
		virtual void forEachPlayer(ForEachPlayer cb, void* data);
		virtual bool registerModule(const char* name, IModule* module);
		virtual IModule* getModule(const char* name);
		virtual cfg_mgr& get_cfg_mgr();

	private:
		HotSwapService* mService;
	};
}

#endif