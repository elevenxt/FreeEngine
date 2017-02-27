
/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_HOTSWAPPLUGIN_
#define _FF_HOTSWAPPLUGIN_

#include "HotSwapService.h"
#include "base.h"

#ifdef UT_PLATFORM_WINDOWS
#define DLLImport __declspec(dllimport)
#define DLLExport __declspec(dllexport)
#else
#define DLLImport
#define DLLExport
#endif

#include <cinttypes>

namespace ff
{
	/**
	* 可热更新的逻辑
	*/
	class HotSwapPlugin
	{
	public:
		virtual bool init(HotSwapService* serve) = 0;
		virtual void unit() = 0;
		// 可以处理网络消息
		virtual int32_t netMsg(Player& player, int32_t msgid, const char* msg, int32_t len) = 0;
	};
}

extern "C"
{
	typedef ff::HotSwapPlugin*(*GetPlugin)();
}

#endif