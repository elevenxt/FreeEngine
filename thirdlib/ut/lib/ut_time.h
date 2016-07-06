/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_TIME_H_
#define _UT_TIME_H_

#include "ut_def.h"

__C_BEGIN_DECLS


/**
* 获取相对毫秒计数值
*
* @return 毫秒计数值
*/
int64_t ut_gettickcount();

int64_t	ut_time_seconds();

__C_END_DECLS

#endif