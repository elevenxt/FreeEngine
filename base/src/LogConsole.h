/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_LOG_CONSOLE_
#define _US_LOG_CONSOLE_

#include "ILog.h"

namespace ff
{
	/*打印日志到控制台*/
	class LogConsole : public Log
	{
	public:
		bool doLog(LogLevel level, const std::string& msg);
	};
}
#endif