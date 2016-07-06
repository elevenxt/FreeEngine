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

#ifdef UT_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#ifdef UT_PLATFORM_WINDOWS
int32_t ut_lasterror()
{
	return GetLastError();
}
int32_t ut_wsalasterror()
{
	return WSAGetLastError();
}
#endif
#ifdef UT_PLATFORM_LINUX
int32_t ut_lasterror()
{
	return errno;
}
int32_t ut_wsalasterror()
{
	return errno;
}
#endif

