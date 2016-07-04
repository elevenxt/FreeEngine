/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_TIMER_
#define _US_TIMER_

#include <cinttypes>
#include <chrono>


namespace ff
{
	class Timer
	{
	public:
		static int64_t getTickCount();
	};
}

#endif