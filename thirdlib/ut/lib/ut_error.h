/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef __UT_ERROR_H_
#define __UT_ERROR_H_

#include "ut_def.h"

__C_BEGIN_DECLS

#define UT_CORE_LOG(file, fmt, ...) do{ut_core_log(file, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__);}while(0)

int32_t ut_core_log(const char* outfile, const char* debugfile, int32_t debugfileline,
			 const char* debugfunction, const char *fmt, ...);

int32_t ut_lasterror();

__C_END_DECLS

#endif 
