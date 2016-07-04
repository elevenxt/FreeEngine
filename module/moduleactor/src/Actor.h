/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_ACTOR_
#define _US_ACTOR_

#include <string>
#include <vector>
#include <cinttypes>
#include <functional>

#include "Spinlock.h"
#include "ActorWork.h"

namespace ff
{
	class Actor
	{
	public:
		virtual bool initialize() = 0;
		virtual void finalize() = 0;

		virtual int32_t loopTick(int32_t delta);
		virtual int64_t loopProcess(int64_t delta);

		void dispatchWork(ActorWork* work);
		void poolActorWork();

	private:
		virtual bool doWork(ActorWork* work) = 0;

	private:
		Spinlock				mLock;
		std::vector<ActorWork*>	mWorks;
		std::vector<ActorWork*>	mFinished;
	};
}

#endif
