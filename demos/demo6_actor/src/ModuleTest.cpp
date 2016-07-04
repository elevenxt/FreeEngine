/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <functional>

#include "ModuleTest.h"
#include "base.h"

#include "ModuleMgr.h"
#include "ModuleActor.h"
#include "ActorNormalWorker.h"

using namespace ff::demo;

bool ModuleTest::initialize()
{
	ff::ModuleActor* pActor = ff::ModuleMgr::instance().getModule<ff::ModuleActor>();
	SYS_VERIFY_RV(pActor != nullptr, false);
	/*注册4个普通的任务处理*/
	for (int32_t i=0; i<4; i++)
	{
		pActor->registerActor("normal", new ff::ActorNormalWorker());
	}

	/*添加8个耗时的任务*/
	for (int32_t i=0; i<8; i++)
	{
		ff::ActorNormalWorker::Work* work = new ff::ActorNormalWorker::Work(std::bind(&ModuleTest::hardwork, this));
		work->setCallback(std::bind(&ModuleTest::workfinish, this, std::placeholders::_1), 10000);
		pActor->dispatchWork("normal", work);
	}

	return true;
}

void ModuleTest::finalize()
{
	
}

void ModuleTest::hardwork()
{
	SYSLOG_DEBUG("work start in actor thread.");
	// 很耗时的操作,这个在actor线程中操作
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void ModuleTest::workfinish(ff::ActorWork* work)
{
	// 通知任务完成，这个是由主线程调用
	SYSLOG_DEBUG("work finished in main thread.");
}