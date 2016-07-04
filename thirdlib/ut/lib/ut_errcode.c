/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_errcode.h"


ut_err_code_t	ut_make_err_code(int32_t code)
{
	ut_err_code_t err_code;
	err_code.code = code;
	return err_code;
}

int32_t	ut_isequal(ut_err_code_t c1, ut_err_code_t c2)
{
	return c1.code == c2.code;
}

int32_t ut_get_errcode(ut_err_code_t errcode)
{
	return errcode.code;
}

int32_t	ut_ec_issuccess(ut_err_code_t errcode)
{
	return ut_isequal(errcode, ut_success);
}

int32_t	ut_ec_iserror(ut_err_code_t errcode)
{
	return !ut_isequal(errcode, ut_success);
}