/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_SYSLOG_
#define _US_SYSLOG_

#include <cinttypes>

#include "Singleton.h"
#include "Spinlock.h"
#include "ILog.h"

namespace ff
{
	// 系统日志
	class Syslog : public Singleton<Syslog>
	{
	public:
		bool initialize();
		void finalize();
		Log* redirect(Log* log);
		void doLog(Log::LogLevel level, const std::string& msg);

	private:
		Log*	mLog = nullptr;
	};	

	void SyslogTrace(const std::string& msg);
	void SyslogDebug(const std::string& msg);
	void SyslogNotice(const std::string& msg);
	void SyslogWarning(const std::string& msg);
	void SyslogError(const std::string& msg);
	void SyslogFatal(const std::string& msg);
}
#endif