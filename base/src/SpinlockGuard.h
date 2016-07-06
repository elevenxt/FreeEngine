/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_SPINLOCK_GUARD
#define _US_SPINLOCK_GUARD


#include "Spinlock.h"

namespace ff
{
	class SpinlockGuard
	{
	private:
		SpinlockGuard(const SpinlockGuard&) = delete;
		void operator=(const SpinlockGuard&) = delete;

	public:
		SpinlockGuard(Spinlock& lock) :mLock(lock)
		{
			mLock.lock();
		}

		~SpinlockGuard()
		{
			mLock.unlock();
		}

	private:
		Spinlock& mLock;
	};
}

#endif