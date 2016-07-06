/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#include "ut_time.h"
#include <time.h>

#ifdef UT_PLATFORM_LINUX
#include <sys/time.h>

int64_t ut_gettickcount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#endif

#ifdef UT_PLATFORM_WINDOWS
#include <windows.h>

int64_t ut_gettickcount()
{
	return GetTickCount();
}

#endif

int64_t	ut_time_seconds()
{
	return time(0);
}
