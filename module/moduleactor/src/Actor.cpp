/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "Actor.h"
#include "SpinlockGuard.h"

using namespace ff;

int32_t Actor::loopTick(int32_t delta)
{
	return 1;
}

int64_t Actor::loopProcess(int64_t delta)
{
	std::vector<ActorWork*> works;
	{
		SpinlockGuard lock(mLock);
		works = mWorks;
		mWorks.clear();
	}

	for (std::vector<ActorWork*>::iterator iter = works.begin();
		iter != works.end(); ++iter)
	{
		doWork(*iter);
	}

	{
		SpinlockGuard lock(mLock);
		for (std::vector<ActorWork*>::iterator iter = works.begin();
			iter != works.end(); ++iter)
		{
			mFinished.push_back(*iter);
		}
	}

	return 1;
}

void Actor::dispatchWork(ActorWork* work)
{
	SpinlockGuard lock(mLock);
	mWorks.push_back(work);
}

void Actor::poolActorWork()
{
	std::vector<ActorWork*> works;

	{
		SpinlockGuard lock(mLock);
		works = mFinished;
		mFinished.clear();
	}

	for (std::vector<ActorWork*>::iterator iter = works.begin();
		iter != works.end(); ++iter)
	{
		(*iter)->doCallback();
		delete *iter;
	}
}

