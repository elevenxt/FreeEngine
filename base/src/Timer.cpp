/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "Timer.h"

using namespace ff;

int64_t Timer::getTickCount()
{
	static const std::chrono::steady_clock::time_point ApplicationStartTime = std::chrono::steady_clock::now();
	return int64_t(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - ApplicationStartTime).count());
}