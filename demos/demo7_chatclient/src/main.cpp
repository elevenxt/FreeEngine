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

#include "ModuleClient.h"
#include "ModuleNetService.h"

namespace ff
{
	namespace demo
	{
		class ServerFramework : public Framework
		{
		private:


		protected:
			virtual bool initialize()
			{
				// 先注册所有模块
				SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleClient>(), false);
				SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleNetService>(), false);

				return true;
			}

			virtual void finalize()
			{

			}
		};

		static ServerFramework app;
	}
}
