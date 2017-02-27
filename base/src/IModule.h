/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_MODULE_
#define _FF_MODULE_

#include "ModuleMgr.h"

namespace ff
{
	/*
		所有模块的基类
	*/
	class IModule
	{
	public:
		virtual ~IModule() {}
		/*模块自身的初始化函数，此函数内不要调用其它模块的成员函数*/
		virtual bool initialize(ModuleMgr& mgr)	= 0;
		/*系统即将关闭时调用*/
		virtual	void finalize()		= 0;
		/*系统主循环开始前调用*/
		virtual void preStartLoop() {};
	};
}
#endif