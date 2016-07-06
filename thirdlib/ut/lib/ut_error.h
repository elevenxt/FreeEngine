/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef __UT_ERROR_H_
#define __UT_ERROR_H_

#include "ut_def.h"

__C_BEGIN_DECLS


int32_t ut_lasterror();
int32_t ut_wsalasterror();

__C_END_DECLS

#endif 
