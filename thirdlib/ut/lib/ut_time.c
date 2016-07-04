/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#include "ut_time.h"
#include <time.h>

#ifdef UT_PLATFORM_LINUX
#include <sys/time.h>

ut_time_t ut_gettime()
{
	ut_time_t ut;

	time_t now;   
	struct tm *timenow;    
	time(&now);   
	timenow = localtime(&now);   

	ut.year = timenow->tm_year+1900;
	ut.month = timenow->tm_mon;
	ut.day = timenow->tm_mday;
	ut.hour = timenow->tm_hour;
	ut.minute = timenow->tm_min;
	ut.second = timenow->tm_sec;

	return ut;
}


int64_t ut_gettickcount()
{
	static struct timeval tv_start;
	static struct timeval* tvs = 0;
	if (tvs == 0)
	{
		tvs = &tv_start;
		gettimeofday(tvs, 0);
	}

	struct timeval tv;
	gettimeofday(&tv, 0);
	return ((tv.tv_sec-tv_start.tv_sec+1) * 1000 + tv.tv_usec / 1000);
}

#endif

#ifdef UT_PLATFORM_WINDOWS
#include <windows.h>

ut_time_t ut_gettime()
{
	ut_time_t ut;

	SYSTEMTIME systime;
	GetLocalTime(&systime);

	ut.year = systime.wYear;
	ut.month = systime.wMonth;
	ut.day = systime.wDay;
	ut.hour = systime.wHour;
	ut.minute = systime.wMinute;
	ut.second = systime.wSecond;

	return ut;
}

int64_t ut_gettickcount()
{
	return GetTickCount();
}

#endif

int64_t	ut_time_seconds()
{
	return time(0);
}
