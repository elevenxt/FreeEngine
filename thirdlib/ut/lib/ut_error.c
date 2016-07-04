/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/




#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "ut_error.h"
#include "ut_time.h"

#ifdef UT_PLATFORM_WINDOWS
#include <Windows.h>
#pragma warning(push)
#pragma warning(disable:4996)
#endif

int32_t ut_core_log(const char* outfile, const char* debugfile, int32_t debugfileline,
			 const char* debugfunction, const char *fmt, ...)
{
	ut_time_t utime;
	va_list args;

	FILE* of = fopen(outfile, "a+");
	if (0 == of)
	{
		return -1;
	}
	
	utime = ut_gettime();
	fprintf(of, "[%4d/%2d/%2d - %2d:%2d:%2d] - ",
		utime.year, utime.month, utime.day, 
		utime.hour, utime.minute, utime.second);

	fprintf(of, "\t[%s]-[%s:%d] \r\n",
		debugfunction, debugfile, debugfileline);

	va_start(args, fmt);
	vfprintf(of, fmt, args);
	va_end(args);
	fclose(of);

	return 0;
}

#ifdef UT_PLATFORM_WINDOWS
int32_t ut_lasterror()
{
	return GetLastError();
}
#endif
#ifdef UT_PLATFORM_LINUX
int32_t ut_lasterror()
{
	return errno;
}
#endif

#ifdef UT_PLATFORM_WINDOWS
#pragma warning(pop)
#endif
