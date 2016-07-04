/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#ifndef _UT_SPRINTF_
#define _UT_SPRINTF_

#include "ut_def.h"

__C_BEGIN_DECLS

#include <stdarg.h>
#include <stdlib.h>

int32_t ut_snprintf(char* dstbuf, int32_t bufsize, const char* fmt, ...);
int32_t ut_svnprintf(char* dstbuf, int32_t bufsize, const char* fmt, va_list argptr);

__C_END_DECLS

#endif

