/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_MEMORY_H_
#define _UT_MEMORY_H_

#include "ut_def.h"

void*	ut_new(int32_t size);
void	ut_delete(void* ptr);

#define UT_NEW(T)					(T*)ut_new(sizeof(T))
#define UT_NEW_ARRAY(T, num)		(T*)ut_new(sizeof(T)*num)
#define UT_DELETE(PTR)				{ut_delete((void*)PTR);PTR=0;}


#endif