/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_MODULE_COMPONENT_MGR_
#define _FF_MODULE_COMPONENT_MGR_

#include <cinttypes>
#include <string>
#include "IModule.h"
namespace ff
{
	/*
		模块组件管理器
	*/
	class IComponentMgr
	{
	public:
		/*主线程每贞会调用tick*/
		virtual void tick(int32_t delta) = 0;
		virtual bool registerModule(std::string name, IModule* module) = 0;
		virtual bool initialize() = 0;
		virtual void finalize() = 0;
	};
}

#endif