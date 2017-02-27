/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_TALK_
#define _FF_MODULE_TALK_

#include <map>
#include <string>
#include "Player.h"
#include "MsgMgr.h"
#include "IModule.h"
#include "csmsg.h"

namespace ff
{
	class ModuleTalk : public IModule
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

	public:
		int netMsg(Player& player, const cs_talk& msg);
	};
}

#endif
