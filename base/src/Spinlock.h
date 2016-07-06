/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_SPINLOCK_
#define _US_SPINLOCK_

#include <atomic>
#include <memory>

namespace ff
{
	// 自旋锁
	class Spinlock
	{
	public:
		Spinlock();
		bool isValidate();
		bool trylock();
		void lock();
		void unlock();

	private:
		std::shared_ptr<std::atomic<int32_t>>	mValue;
	};
}

#endif