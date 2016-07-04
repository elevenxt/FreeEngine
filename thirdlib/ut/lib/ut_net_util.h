/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _NET_UTIL_
#define _NET_UTIL_

#include "ut_defines.h"

__C_BEGIN_DECLS


#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include "ut_error.h"


#ifdef UT_PLATFORM_LINUX
#define INVALID_SOCKET		(-1)
#define SOCKET_ERROR		(-1)
#else
#define MSG_NOSIGNAL 0
#endif

typedef int32_t sock_handle_t;

#define SOCKET_SUCCESS	(0)

#define LISTEN_QUE_SIZE	128

__C_END_DECLS

#endif
