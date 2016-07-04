/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#ifndef _UT_DEFINES_H_
#define _UT_DEFINES_H_

#include "ut_def.h"
#include <assert.h>
#include "ut_errcode.h"
#include "ut_error.h"



#define UT_ASSERT_R(x)		do{if (!(x)){assert(x);return;}}while(0)
#define UT_ASSERT_RV(x,v)	do{if (!(x)){assert(x);return v;}}while(0)
#define UT_CHECKT_R(x)		do{if (!(x)){return;}}while(0)
#define UT_CHECK_RV(x,v)	do{if (!(x)){return v;}}while(0)

#define UT_CHECK_TRUE(con)		do{ if(!(con)){goto FAIL;} } while (0)
#define UT_CHECK_SUCCESS(con)	do{ if(ut_ec_iserror(con)){goto FAIL;} } while (0)
#define UT_VERIFY_TRUE(con)		do{ if(!(con)){assert(!#con);goto FAIL;} } while (0)
#define UT_VERIFY_SUCCESS(con)	do{ if(ut_ec_iserror(con)){assert(!#con);goto FAIL;} } while (0)

#define UT_ASSERT_TRUE(con)		do{ if(!(con)){assert(!#con);} } while (0)
#define UT_ASSERT_SUCCESS(con)	do{ if(ut_ec_iserror(con)){assert(!#con);} } while (0)
#define UT_ASSERT_FAIL(con)		do{ if(ut_ec_issuccess(con)){assert(!#con);} } while (0)

#endif 