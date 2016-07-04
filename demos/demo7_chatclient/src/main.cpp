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
				ModuleMgr& mgr = ModuleMgr::instance();
				SYS_VERIFY_RV(mgr.registerModule<ModuleClient>(), false);
				SYS_VERIFY_RV(mgr.registerModule<ModuleNetService>(), false);

				// 初始化模块管理器
				SYS_VERIFY_RV(mgr.initialize(), false);;

				return true;
			}

			virtual void finalize()
			{
				ModuleMgr::instance().finalize();
			}
		};

		static ServerFramework app;
	}
}
