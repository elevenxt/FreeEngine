/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <thread>
#include <cinttypes>

#include "Framework.h"
#include "ModuleMgr.h"
#include "base.h"
#include "Timer.h"
#include "ComponentTick.h"
#include "ComponentRunnable.h"


using namespace ff;

static Framework* sInstance = nullptr;

Framework::Framework()
{
	sInstance = this;
}

Framework::~Framework()
{

}

Framework* Framework::instance()
{
	return sInstance;
}

void Framework::startLoop()
{
	mModuleMgr.preStartLoop();

	static int64_t bt = Timer::getTickCount();
	int64_t ct = 0;
	SYSLOG_NOTICE("★★★★★★★★★★★ {} {} Server start	★★★★★★★★★★★",  (char)1, (char)2);
	while (true)
	{
		ct = Timer::getTickCount();
		if (ct <= bt)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		mModuleMgr.tick(ct - bt);
		bt = ct;
	}
}

bool Framework::doInit()
{	
	SYS_VERIFY_RV(mModuleMgr.addComponentMgr<ComponentTickMgr>(), false);
	SYS_VERIFY_RV(mModuleMgr.addComponentMgr<ComponentRunnableMgr>(), false);

	SYS_VERIFY_RV(initialize(), false);

	// 初始化模块管理器
	SYS_VERIFY_RV(mModuleMgr.initialize(), false);

	SYSLOG_TRACE("Framework initialize success.");

	return true;
}

void Framework::doUninit()
{
	finalize();
	mModuleMgr.finalize();
	SYSLOG_TRACE("Framework finalize over.");
}
