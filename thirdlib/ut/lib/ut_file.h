/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_FILE_H_
#define _UT_FILE_H_

#include "ut_def.h"

__C_BEGIN_DECLS


/**
* 获取文件修改时间
*
* @return 毫秒计数值
*/
int64_t ut_file_modifytime(const char* fname);

__C_END_DECLS

#endif