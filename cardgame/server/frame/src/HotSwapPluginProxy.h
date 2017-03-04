
/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_HOTSWAPPLUGIN_PROXY_
#define _FF_HOTSWAPPLUGIN_PROXY_
#include <cinttypes>
#include "HotSwapPlugin.h"
#include "Singleton.h"

namespace ff
{	
	class HotSwapPluginProxy : public HotSwapPlugin, public Singleton<HotSwapPluginProxy>
	{
	public:
		HotSwapPluginProxy();
		bool good();
		void reset(HotSwapPlugin* impl);

		virtual bool init(HotSwapService* serve);
		virtual void unit();
		virtual int32_t netMsg(Player& player, int32_t msgid, const char* msg, int32_t len);

	private:
		HotSwapPlugin* mImpl;
	};
}


#endif