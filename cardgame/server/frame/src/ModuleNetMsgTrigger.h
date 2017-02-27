/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_NETMSG_TRIGGER_
#define _FF_MODULE_NETMSG_TRIGGER_

#include <map>
#include <string>
#include "IModule.h"
#include "NetService.h"
#include "Player.h"
#include "MsgMgr.h"

#include "csmsg.h"
#include "ModuleDataSync.h"

namespace ff
{
	class ModuleNetMsgTrigger : public IModule, public NetService::Listener
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

		template<typename CLASS, typename PROTO>
		bool registerMsgProcessor(CLASS* c, int32_t(CLASS::*func)(Player&, const PROTO&))
		{
			return mMsgMgr.msgConnect<PROTO>(std::bind(func, c, std::placeholders::_1, std::placeholders::_2));
		}

	private:
		virtual void newconn(ff::NetService* netService, int32_t netid);
		virtual void lostconn(ff::NetService*, int32_t netid);
		virtual void recvdata(ff::NetService*, int32_t netid, const char* msg, int32_t len);


	private:
		NetService* mNetService;
		MsgMgr<Player, csmsg_group> mMsgMgr;

		ModuleDataSync* mModuleDataSync;
	};

#define REG_NETMSG(mgr, cla, func, msg)	mgr->registerMsgProcessor<cla, msg>(this, &cla::func)

}

#endif
