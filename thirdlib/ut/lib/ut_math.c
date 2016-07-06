/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/




#include "ut_math.h"


rand_handle_t	ut_seed(int32_t seed)
{
	rand_handle_t sh;
	sh.seed = seed;
	return sh;
}

int32_t		ut_rand(rand_handle_t* sh)
{
	return( ((sh->seed = sh->seed * 214013L
		+ 2531011L) >> 16) & 0x7fff );
}

int32_t		ut_rand_range(rand_handle_t* sh, int32_t min, int32_t max)
{
	if (max == min)
	{
		return min;
	}

	return ut_rand(sh)%(max-min) + min;
}

int32_t		ut_min(int32_t a, int32_t b)
{
	return a > b ? b : a;
}

int32_t		ut_max(int32_t a, int32_t b)
{
	return a > b ? a : b;
}

int32_t		ut_clip(int32_t v, int32_t min, int32_t max)
{
	if (v < min)
	{
		v = min;
	}
	if (v > max)
	{
		v = max;
	}
	return v;
}