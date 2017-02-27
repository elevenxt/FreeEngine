/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_MODULE_HOTSWAP_
#define _FF_MODULE_HOTSWAP_

#include <map>
#include <string>
#include <cinttypes>
#include <vector>
#include <memory>

#include "IModule.h"
#include "ComponentRunnable.h"
#include "ComponentTick.h"
#include "HotSwapServiceImpl.h"
#include "ut_dll.h"
#include "HotSwapPluginProxy.h"

namespace ff
{
	/**
	* »»º”‘ÿ¬ﬂº≠
	*/
	class ModuleHotSwap : public IModule
		, public ComponentRunnable
		, public ComponentTick
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();
		virtual int32_t runOnce();
		virtual int64_t loopTick(int64_t delta);

	};
}
#endif