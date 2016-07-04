/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_ACTORNORMALWORKER_
#define _US_ACTORNORMALWORKER_

#include "Actor.h"
#include <cinttypes>

namespace ff
{
	class ActorNormalWorker : public Actor
	{
	public:
		class Work : public ActorWork
		{
			friend class  ActorNormalWorker;
		public:			
			Work(std::function<void()> work);
			
		private:
			std::function<void()> mWork;
		};

		virtual bool initialize();
		virtual void finalize();

		virtual int32_t loopTick(int32_t delta);

		void dispatchWork(ActorWork* work);
		void poolActorWork();

	private:
		virtual bool doWork(ActorWork* work);

	private:
		Spinlock				mLock;
		std::vector<ActorWork*>	mWorks;
		std::vector<ActorWork*>	mFinished;
	};
}

#endif
