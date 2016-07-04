/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_memory.h"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>


void*	ut_new(int32_t size)
{
	void* p = malloc(size);
	memset(p, 0, size);
	return p;
}

void	ut_delete(void* ptr)
{
	free(ptr);
}