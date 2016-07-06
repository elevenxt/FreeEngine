/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <stdio.h>
#include "base.h"
#include "LogConsole.h"

#ifdef UT_PLATFORM_WINDOWS
#include <windows.h>
#endif

using namespace ff;

bool LogConsole::doLog(Log::LogLevel level, const std::string& msg)
{
#ifdef UT_PLATFORM_WINDOWS
	DWORD col = FOREGROUND_RED;

	switch (level)
	{
	case LogLevel::L_FATAL:
		col = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case LogLevel::L_ERROR:
		col = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case LogLevel::L_WARNING:
		col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case LogLevel::L_NOTICE:
		col = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case LogLevel::L_DEBUG:
		col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case LogLevel::L_TRACE:
		col = FOREGROUND_INTENSITY;
		break;
	default:
		col = FOREGROUND_RED;
		break;
	}
	HANDLE consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consolehwnd, (WORD)col);
#endif
#ifdef UT_PLATFORM_LINUX
	static const char* none = "\033[0m"; (void)none;
	static const char* black = "\033[0;30m"; (void)black;
	static const char* dark_gray = "\033[1;30m"; (void)dark_gray;
	static const char* blue = "\033[0;34m"; (void)blue;
	static const char* light_blue = "\033[1;34m"; (void)light_blue;
	static const char* green = "\033[0;32m"; (void)green;
	static const char* light_green = "\033[1;32m"; (void)light_green;
	static const char* cyan = "\033[0;36m"; (void)cyan;
	static const char* light_cyan = "\033[1;36m"; (void)light_cyan;
	static const char* red = "\033[0;31m"; (void)red;
	static const char* light_red = "\033[1;31m"; (void)light_red;
	static const char* purple = "\033[0;35m"; (void)purple;
	static const char* light_purple = "\033[1;35m"; (void)light_purple;
	static const char* brown = "\033[0;33m"; (void)brown;
	static const char* yellow = "\033[1;33m"; (void)yellow;
	static const char* light_gray = "\033[0;37m"; (void)light_gray;
	static const char* white = "\033[1;37m"; (void)white;

	switch (level)
	{
	case LogLevel::L_FATAL:
		printf("%s", purple);
		break;
	case LogLevel::L_ERROR:
		printf("%s", red);
		break;
	case LogLevel::L_WARNING:
		printf("%s", yellow);
		break;
	case LogLevel::L_NOTICE:
		printf("%s", green);
		break;
	case LogLevel::L_DEBUG:
		printf("%s", white);
		break;
	case LogLevel::L_TRACE:
		printf("%s", light_gray);
		break;
	default:
		printf("%s", red);
		break;
	}
#endif // UT_PLATFORM_LINUX
	fprintf(stdout, "%s\n", msg.c_str());

	return true;
}