/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#include "ut_sprintf.h"
#include "ut_defines.h"
#include <stdio.h>

int32_t ut_snprintf(char* dstbuf, int32_t bufsize, const char* fmt, ...)
{
	int32_t nr = 0;
	va_list arglist;
	va_start(arglist, fmt);
	nr = ut_svnprintf(dstbuf, bufsize, fmt, arglist);
	va_end(arglist);

	return nr;
}

int32_t ut_svnprintf(char* dstbuf, int32_t bufsize, const char* fmt, va_list argptr)
{
	UT_ASSERT_RV (dstbuf!=0 && bufsize>0 && fmt!=0, -1);

#ifdef UT_PLATFORM_WINDOWS
	return vsnprintf_s(dstbuf, bufsize, _TRUNCATE, fmt, argptr);
#else
	return vsnprintf(dstbuf, bufsize, fmt, argptr);
#endif
}