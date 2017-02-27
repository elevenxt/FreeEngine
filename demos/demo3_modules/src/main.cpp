/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <cinttypes>
#include <string>
#include <functional>

#include "base.h"
#include "ModuleMgr.h"
#include "Framework.h"
#include "ModuleMgr.h"
#include "Config.h"

#include "ModuleTest1.h"
#include "ModuleTest2.h"
#include "ModuleTest3.h"

namespace ff
{
	namespace demo
	{
		class ServerFramework : public ff::Framework
		{
		protected:
			virtual bool initialize()
			{
				// 先注册所有模块
				SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleTest1>(), false);
				SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleTest2>(), false);
				SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleTest3>(), false);
				//mgr.registerModule("test", new ModuleTest(), 0);

				return true;
			}

			virtual void finalize()
			{

			}
		};

		static ServerFramework app;
	}
}
