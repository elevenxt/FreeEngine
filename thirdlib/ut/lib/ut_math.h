/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



 
#ifndef _UT_MATH_H_
#define _UT_MATH_H_

// 这个模块还未测试

#include "ut_def.h"

__C_BEGIN_DECLS

typedef struct rand_handle
{
	int32_t seed;
} rand_handle_t;

rand_handle_t	ut_seed(int32_t seed);
int32_t		ut_rand(rand_handle_t* sh);
int32_t		ut_rand_range(rand_handle_t* sh, int32_t min, int32_t max);

int32_t		ut_min(int32_t a, int32_t b);
int32_t		ut_max(int32_t a, int32_t b);
int32_t		ut_clip(int32_t v, int32_t min, int32_t max);

__C_END_DECLS



#endif
