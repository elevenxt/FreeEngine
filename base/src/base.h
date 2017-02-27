
/******************************************************************************
	https://github.com/elevenxt/FreeEngine

	Copyright (C) 2016 Eleven.
	License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

　　	  Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
	Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:
  　　
		The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

/*
	系统日志、条件检查等
*/

#ifndef _FF_BASE_UTIL_
#define _FF_BASE_UTIL_

#include <assert.h>
#include "format.h"
#include "Syslog.h"

/*
	平台检查
*/
#if defined( _WIN64 )
#define UT_PLATFORM_WINDOWS 0
#  define UT_PLATFORM PLATFORM_WINDOWS
#elif defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#define UT_PLATFORM_WINDOWS 0
#  define UT_PLATFORM PLATFORM_WINDOWS
#elif defined( __APPLE_CC__ )
#define UT_PLATFORM_APPLE   2
#  define UT_PLATFORM PLATFORM_APPLE
#elif defined( __INTEL_COMPILER )
#define UT_PLATFORM_INTEL   3
#  define UT_PLATFORM PLATFORM_INTEL
#else
#define UT_PLATFORM_LINUX   1
#  define UT_PLATFORM UT_PLATFORM_LINUX
#endif

/*
	编译器检查
*/
#ifdef _MSC_VER
#define COMPILER_MICROSOFT 0
#  define UT_COMPILER COMPILER_MICROSOFT
#elif defined( __BORLANDC__ )
#define COMPILER_BORLAND   2
#  define UT_COMPILER COMPILER_BORLAND
#elif defined( __INTEL_COMPILER )
#define COMPILER_INTEL     3
#  define UT_COMPILER COMPILER_INTEL
#elif defined( __GNUC__ )
#define COMPILER_GNU       1
#  define UT_COMPILER COMPILER_GNU
#  define UT_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#  error "FATAL ERROR: Unknown compiler."
#endif

#define SYSLOG0(LEVEL, FMT, ...)	\
	do{	\
		std::string body;	\
		try{	\
			body = fmt::format(FMT);	\
		}	\
		catch (...){	\
			body = "format error";	\
		}	\
		std::string tail = fmt::format("[{}][{}:{}]", __FUNCTION__, __FILE__, __LINE__);	\
		ff::Syslog::instance().doLog(ff::Log::LogLevel::LEVEL, body + tail);	\
		} while (false)

#define SYSLOG(LEVEL, ...)	\
	do{	\
		std::string body;	\
		try{	\
			body = fmt::format(__VA_ARGS__ );	\
		}	\
		catch (...){	\
			SYSLOG0(LEVEL, __VA_ARGS__);	\
		}	\
		std::string tail = fmt::format("[{}][{}:{}]", __FUNCTION__, __FILE__, __LINE__);	\
		ff::Syslog::instance().doLog(ff::Log::LogLevel::LEVEL, body + tail);	\
		} while (false)

/*
	系统日志
*/
#define SYSLOG_TRACE(...)	SYSLOG(L_TRACE, __VA_ARGS__)
#define SYSLOG_DEBUG(...)	SYSLOG(L_DEBUG, __VA_ARGS__)
#define SYSLOG_NOTICE(...)	SYSLOG(L_NOTICE, __VA_ARGS__)
#define SYSLOG_WARNING(...)	SYSLOG(L_WARNING, __VA_ARGS__)
#define SYSLOG_ERROR(...)	SYSLOG(L_ERROR, __VA_ARGS__)
#define SYSLOG_FATAL(...)	SYSLOG(L_FATAL, __VA_ARGS__)

/*
	常用条件检查
	CHECK用于系统外条件检查,就是入参检查
	VERIFY是系统自身出了bug，必须修复
*/
#define SYS_CHECK_RV(CON, RV)	\
	do{	\
		bool con = (CON);	\
		if(!con){SYSLOG_WARNING("CHECK failed[{}]", #CON);return RV;}	\
		}while(0)


#define SYS_CHECK_R(CON)	\
	do{	\
		bool con = (CON);	\
		if(!con){SYSLOG_WARNING("CHECK failed[{}]", #CON);return;}	\
		}while(0)


#define SYS_CHECK_G(CON)	\
	do{	\
		bool con = (CON);	\
		if(!con){SYSLOG_WARNING("CHECK failed[{}]", #CON); goto FAIL;}	\
				}while(0)


#define SYS_ASSERT(CON)	\
	do{	\
		bool con = (CON);	\
		if(!con){	\
			SYSLOG_FATAL("ASSERT failed[{}]", #CON);	\
			assert(false && #CON);}	\
		}while(0)


#define SYS_ASSERT_G(CON)	\
	do{	\
		bool con = (CON);	\
		if(!con){	\
			SYSLOG_FATAL("ASSERT failed[{}]", #CON);	\
			assert(false && #CON);}	\
			goto FAIL;	\
			}while(0)


#define SYS_VERIFY_RV(CON, RV)	\
	do{	\
		bool con = (CON);	\
		if(!con){SYSLOG_FATAL("VERIFY failed[{}]", #CON);assert(false && #CON);return RV;}	\
	}while(0)


#define SYS_VERIFY_R(CON)	\
	do{	\
		bool con = (CON);	\
		if(!con){SYSLOG_FATAL("VERIFY failed[{}]", #CON);assert(false && #CON);return;}	\
	}while(0)


#define SYS_VERIFY_G(CON)	\
	do{	\
		bool con = (CON);	\
		if(!con){SYSLOG_FATAL("VERIFY failed[{}]", #CON);assert(false && #CON); goto FAIL;}	\
	}while(0)


#endif

