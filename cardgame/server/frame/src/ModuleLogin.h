/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_LOGIN_
#define _FF_MODULE_LOGIN_

#include "IModule.h"
#include "Player.h"

#include "csmsg.h"
#include "scmsg.h"

#include "ModuleRocksDb.h"
#include "ModuleDataSync.h"

namespace ff
{
	class ModuleLogin : public IModule
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

	public:
		int32_t netMsg(Player& player, const cs_login& msg);

	private:
		ff::ModuleRocksDb*	mModuleRocksDb;
		ModuleDataSync*		mModuleDataSync;
	};
}

#endif
