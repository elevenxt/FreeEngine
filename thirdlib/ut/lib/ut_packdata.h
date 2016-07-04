/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_PACKDATA_H_
#define _UT_PACKDATA_H_

#include "ut_def.h"

__C_BEGIN_DECLS

int32_t ut_pack_int(int32_t val, char* data, int32_t dl);
int32_t ut_unpack_int(int32_t* val, char* data, int32_t dl);

int32_t ut_pack_data(const char* sz, int32_t szl, char* data, int32_t dl);
int32_t ut_unpack_data(char* sz, int32_t* szl, char* data, int32_t dl);

__C_END_DECLS

#endif