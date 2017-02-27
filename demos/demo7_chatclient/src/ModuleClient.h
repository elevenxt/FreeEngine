/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_CLIENT_
#define _US_MODULE_CLIENT_

#include <vector>
#include <cinttypes>

#include "IModule.h"
#include "NetService.h"
#include "ComponentRunnable.h"
#include "Spinlock.h"

namespace ff
{
	namespace demo
	{
		class ModuleClient : public ff::IModule, public ff::ComponentRunnable, public ff::NetService::Listener
		{
		public:
			virtual bool initialize(ModuleMgr& mgr);
			virtual	void finalize();

		private:
			virtual int32_t runOnce();

			virtual void newconn(ff::NetService* net, int32_t id);
			virtual void lostconn(ff::NetService* net, int32_t id);
			virtual void recvdata(ff::NetService* net, int32_t id, const char* data, int32_t datalen);

		private:
			ff::NetService*		 mNet;
			int32_t			 mId;
			Spinlock		mLock;
		};
	}
}

#endif
