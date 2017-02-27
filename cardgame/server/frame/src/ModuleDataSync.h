/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _FF_MODULE_SAVEDATA_
#define _FF_MODULE_SAVEDATA_

#include <cinttypes>
#include "IModule.h"
#include "ComponentTick.h"
#include "ModuleRocksDb.h"
#include "PlayerImpl.h"

namespace ff
{
	class ModuleDataSync : public IModule, public ComponentTick
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();

	private:
		virtual int64_t loopTick(int64_t delta);

	public:
		bool syncData(Player& player);
		void syncDirtyData();
		void saveDirtyData();

		int32_t savePlayerData(PlayerImpl& player);

	private:
		ModuleRocksDb* mModuleRocksDb;
	};
}

#endif
