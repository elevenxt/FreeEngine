/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ActorNormalWorker.h"
#include "ModuleActor.h"
#include "base.h"

using namespace ff;

ActorNormalWorker::Work::Work(std::function<void()> work)
{
	mWork = work;
}

bool ActorNormalWorker::initialize()
{
	return true;
}

void ActorNormalWorker::finalize()
{

}

int32_t ActorNormalWorker::loopTick(int32_t delta)
{
	return 1;
}

bool ActorNormalWorker::doWork(ActorWork* work)
{
	ActorNormalWorker::Work* nwork = dynamic_cast<ActorNormalWorker::Work*>(work);
	SYS_VERIFY_RV(nwork != nullptr, false);
	nwork->mWork();

	return true;
}