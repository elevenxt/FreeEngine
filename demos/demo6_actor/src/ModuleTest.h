/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_TEST_
#define _US_MODULE_TEST_

#include "IModule.h"
#include "ActorWork.h"

namespace ff
{
	namespace demo
	{
		class ModuleTest : public ff::IModule
		{
		public:
			virtual bool initialize(ModuleMgr& mgr);
			virtual	void finalize();

		private:
			void hardwork();
			void workfinish(ActorWork* work);
		};
	}
}

#endif
