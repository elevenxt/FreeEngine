/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ut_def.h"

#include <string>
#include "CommandLineOption.h"
#include "Config.h"
#include "Framework.h"

#ifdef UT_PLATFORM_LINUX
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#endif

#ifdef UT_PLATFORM_WINDOWS
#include <windows.h>
#include <DbgHelp.h>
#include <time.h>
#endif

#include "base.h"

#ifdef UT_PLATFORM_WINDOWS

#pragma comment( lib, "DbgHelp" )

// 创建Dump文件
void CreateDumpFile(const std::string& strDumpFilePathName, EXCEPTION_POINTERS* pException)
{
	// 创建Dump文件
	HANDLE hDumpFile = CreateFile(strDumpFilePathName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump信息
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// 写入Dump文件内容
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}

// 处理Unhandled Exception的回调函数
long ApplicationCrashHandler(EXCEPTION_POINTERS* pException)
{
	time_t t = time(0);
	char szDmupName[MAX_PATH];
	tm* ptm = localtime(&t);

	sprintf(szDmupName, "%d_%d_%d_%d_%d_%d.dmp", ptm->tm_year + 1900, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	CreateDumpFile(szDmupName, pException);

	FatalAppExit(-1, szDmupName);

	return EXCEPTION_EXECUTE_HANDLER;
}
#endif

#ifdef UT_PLATFORM_LINUX
void InitDaemon()
{
	daemon(1, 0);
	// ignore signals
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
#else
void CloseXButton()
{
	HWND hWnd = GetConsoleWindow();
	if (hWnd)
	{
		HMENU hMenu = GetSystemMenu(hWnd, FALSE);
		EnableMenuItem(hMenu, SC_CLOSE, MF_DISABLED | MF_BYCOMMAND);
	}
}

void InitDaemon()
{
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
	//CloseXButton();
	SetConsoleTitle(ff::Config::instance().get("name").c_str());
}
#endif

int main(int argc, char* argv[])
{
	ff::CommandLineOption option;
	option.setOption("d", false);
	if (!option.parse(argc, argv))
	{
		fprintf(stderr, "command line parse failed.\n");
		return -1;
	}

	if (!ff::Syslog::instance().initialize())
	{
		fprintf(stderr, "syslog init failed.\n");
		return -1;
	}

	if (option.isSet("d"))
	{
		InitDaemon();
	}
	
	SYSLOG_NOTICE("server start...");

	ff::Framework* framework = ff::Framework::instance();
	if (framework == 0)
	{
		SYSLOG_ERROR("Framework instance is null.");
		return 0;
	}

	if (!framework->doInit())
	{
		SYSLOG_ERROR("Framework do init failed.");
		return 0;
	}
	SYSLOG_NOTICE("Framework start loop.");
	framework->startLoop();
	SYSLOG_TRACE("Framework end loop.");
	framework->doUninit();
	SYSLOG_TRACE("Framework end uninit.");	

	SYSLOG_TRACE("server finish over.");

	return 0;
}
