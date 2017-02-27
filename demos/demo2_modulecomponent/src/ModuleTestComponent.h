/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_TESTCOMPONENT_
#define _US_MODULE_TESTCOMPONENT_

#include "IModule.h"
#include "ComponentTick.h"

namespace ff
{
	namespace demo
	{
		class ModuleTestComponent : public ff::IModule, public ff::ComponentTick
		{
		public:
			virtual bool initialize(ModuleMgr& mgr);
			virtual	void finalize();

		private:
			/*
				实现ComponentTick接口函数，loopTick在主线程中被调用，
				返回值是下次调用的间隔
			*/
			virtual int64_t loopTick(int64_t delta);

		private:
			int64_t mTick;
		};
	}
}

#endif
