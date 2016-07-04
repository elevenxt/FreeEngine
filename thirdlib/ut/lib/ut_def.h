/******************************************************************************
	https://github.com/elevenxt/utnet

	Copyright (C) 2016 Eleven.
	License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

		Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
	Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:
	  ¡¡¡¡
		The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/



#ifndef _UT_DEF_H_
#define _UT_DEF_H_

#include <inttypes.h>
#include "ut_errcode.h"

#ifdef  __cplusplus
# define __C_BEGIN_DECLS  extern "C" {
# define __C_END_DECLS    }
#else
# define __C_BEGIN_DECLS
# define __C_END_DECLS
#endif

#ifdef __GNUC__
#define UT_ATTRIBUTE(X) __attribute__(X)
#else
#define UT_ATTRIBUTE(X)
#endif




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

#endif