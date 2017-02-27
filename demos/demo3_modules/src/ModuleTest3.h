/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_TEST3_
#define _US_MODULE_TEST3_

#include "IModule.h"

namespace ff
{
	namespace demo
	{
		class ModuleTest3 : public ff::IModule
		{
		public:
			virtual bool initialize(ModuleMgr& mgr);
			virtual	void finalize();

		public:
			void hello();

		};
	}
}

#endif
