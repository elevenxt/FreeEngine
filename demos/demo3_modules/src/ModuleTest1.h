/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_TEST1_
#define _US_MODULE_TEST1_

#include "IModule.h"
#include "ComponentTick.h"
#include "ModuleTest2.h"

namespace ff
{
	namespace demo
	{
		class ModuleTest1 : public ff::IModule, public ff::ComponentTick
		{
		public:
			virtual bool initialize(ModuleMgr& mgr);
			virtual	void finalize();

		public:
			void hello();

		private:
			virtual int64_t loopTick(int64_t delta);

		private:
			ModuleTest2*	mModuleTest2;
		};
	}
}

#endif
