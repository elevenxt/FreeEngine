/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_ILOG_
#define _US_ILOG_

#include <string>


namespace ff
{
	/*
		日志接口
	*/
	class Log
	{
	public:
		virtual ~Log() {}
		enum class LogLevel
		{
			L_TRACE,
			L_DEBUG,
			L_NOTICE,
			L_WARNING,
			L_ERROR,
			L_FATAL,
		};

		virtual bool doLog(LogLevel level, const std::string& msg) = 0;
	};
}

#endif