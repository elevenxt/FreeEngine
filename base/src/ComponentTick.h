/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_MODULE_COMPONENTTICK__
#define _FF_MODULE_COMPONENTTICK__

#include <map>
#include <string>
#include <vector>
#include <cinttypes>
#include <thread>

#include "Singleton.h"
#include "IModule.h"
#include "IComponentMgr.h"

namespace ff
{
	/*
		模块实现此接口后，loopTick会在主线程中调用，返回值是两次调用间隔
	*/
	class ComponentTick
	{
	public:
		virtual int64_t loopTick(int64_t delta) = 0;
	};

	class ComponentTickMgr : public IComponentMgr
	{
	public:
		virtual void tick(int32_t delta);
		virtual bool registerModule(std::string name, IModule* module);
		virtual bool initialize();
		virtual void finalize();

	private:
		struct ComTicker
		{
			ComponentTick*	ticker;
			int32_t			gap;
			int32_t			left;
		};
		// 所有触发器
		std::vector<ComTicker>		mTickers;
	};
}

#endif