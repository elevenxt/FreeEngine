/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_MSG_TRIGGER_
#define _FF_MODULE_MSG_TRIGGER_
#include <cinttypes>
#include <map>
#include <string>
#include "Player.h"
#include "MsgMgr.h"
#include "IModule.h"
#include "csmsg.h"

namespace ff
{
	class ModuleMsgTrigger : public IModule
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

		template<typename CLASS, typename PROTO>
		bool registerMsgProcessor(CLASS* c, int32_t(CLASS::*func)(Player&, const PROTO&))
		{
			return mMsgMgr.msgConnect<PROTO>(std::bind(func, c, std::placeholders::_1, std::placeholders::_2));
		}

		int triggerNetMsg(Player& player, int32_t msgid, const char* msg, int32_t len);

	private:
		MsgMgr<Player, csmsg_group> mMsgMgr;
	};

#define REG_NETMSG(mgr, cla, func, msg)	mgr->registerMsgProcessor<cla, msg>(this, &cla::func)

}

#endif
