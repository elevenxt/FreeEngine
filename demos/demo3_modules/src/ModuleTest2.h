/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_TEST2_
#define _US_MODULE_TEST2_

#include "IModule.h"
#include "ModuleTest3.h"

namespace ff
{
	namespace demo
	{
		class ModuleTest2 : public ff::IModule
		{
		public:
			virtual bool initialize();
			virtual	void finalize();

		public:
			void hello();

		private:
			ModuleTest3*	mModuleTest3;
		};
	}
}

#endif
