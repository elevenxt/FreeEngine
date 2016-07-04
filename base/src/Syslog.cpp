/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "Syslog.h"
#include "SpinlockGuard.h"
#include "LogConsole.h"

using namespace ff;

bool Syslog::initialize()
{
	if (mLog != nullptr)
	{
		return false;
	}

	mLog = new LogConsole();

	return true;
}

void Syslog::finalize()
{
	if (mLog != nullptr)
	{
		delete mLog;
		mLog = nullptr;
	}
}

Log* Syslog::redirect(Log* log)
{
	Log* old = mLog;
	mLog = log;
	return old;
}

void Syslog::doLog(Log::LogLevel level, const std::string& msg)
{

	if (mLog == nullptr)
	{
		fprintf(stderr, "log error\r\n");
		assert(false && "log error");
		return;
	}

	mLog->doLog(level, msg);
}

namespace ff
{
	void SyslogTrace(const std::string& msg)
	{
		Syslog::instance().doLog(Log::LogLevel::L_TRACE, msg);
	}

	void SyslogDebug(const std::string& msg)
	{
		Syslog::instance().doLog(Log::LogLevel::L_DEBUG, msg);
	}

	void SyslogNotice(const std::string& msg)
	{
		Syslog::instance().doLog(Log::LogLevel::L_NOTICE, msg);
	}

	void SyslogWarning(const std::string& msg)
	{
		Syslog::instance().doLog(Log::LogLevel::L_WARNING, msg);
	}

	void SyslogError(const std::string& msg)
	{
		Syslog::instance().doLog(Log::LogLevel::L_ERROR, msg);
	}

	void SyslogFatal(const std::string& msg)
	{
		Syslog::instance().doLog(Log::LogLevel::L_FATAL, msg);
	}
}