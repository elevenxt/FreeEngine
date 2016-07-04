/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



 
#ifndef _DLL_CLIENT_H_
#define _DLL_CLIENT_H_

// 这个模块还未测试

#include "ut_def.h"
__C_BEGIN_DECLS

typedef void*	dll_handle_t;
typedef	void*	dll_func_handle_t;

dll_handle_t		ut_dll_load(const char *dllname);
dll_func_handle_t	ut_dll_access(dll_handle_t dllmod, const char *func);
void				ut_dll_close(dll_handle_t dllmod);


__C_END_DECLS



#endif
