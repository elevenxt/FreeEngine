
/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#ifndef _US_MODULECOMPONENT_RUNNABLE_
#define _US_MODULECOMPONENT_RUNNABLE_

#include <map>
#include <string>
#include <vector>
#include <cinttypes>
#include <thread>

#include "IModule.h"
#include "IComponentMgr.h"

namespace ff
{
	/*
		模块实现此接口后，runOnce会在另一个线程中调用，返回值是两次runOnce的休眠间隔
	*/
	class ComponentRunnable
	{
	public:
		virtual int32_t runOnce() = 0;
	};

	class ComponentRunnableMgr : public IComponentMgr
	{
	public:
		virtual void tick(int32_t delta);
		virtual bool registerModule(std::string name, IModule* module);
		virtual bool initialize();
		virtual void finalize();

	private:
		struct ComRunnable
		{
			bool running;
			std::thread worker;
			ComponentRunnable*	runnable;
		};
		static int32_t	worker(ComRunnable* com);

		// 有线程的模块
		std::vector<ComRunnable*>	mRunnables;
	};
}

#endif