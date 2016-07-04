/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_ERRCODE_H_
#define _UT_ERRCODE_H_

#include <inttypes.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define ut_success	ut_make_err_code(0)
#define ut_error	ut_make_err_code(-1)

typedef struct ut_err_code{int32_t code;const char* msg;} ut_err_code_t;

ut_err_code_t	ut_make_err_code(int32_t code);
int32_t			ut_isequal(ut_err_code_t c1, ut_err_code_t c2);
int32_t			ut_ec_issuccess(ut_err_code_t errcode);
int32_t			ut_ec_iserror(ut_err_code_t errcode);
int32_t			ut_get_errcode(ut_err_code_t errcode);

#ifdef  __cplusplus
}
#endif

#endif