/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_MODULE_MGR_
#define _FF_MODULE_MGR_

#include <map>
#include <string>
#include <vector>
#include <cinttypes>
#include <thread>

namespace ff
{
	class IModule;
	class IComponentMgr;

	/*
		模块管理器
	*/
	class ModuleMgr
	{
	public:
		void tick(int32_t delta);

		// 必须在添加模块前，添加模块管理器
		template<typename CMPMGR>
		bool addComponentMgr()
		{
			CMPMGR* mgr = new CMPMGR();
			mComponentMgrs.push_back(mgr);
			return true;
		}

		/*注册模块*/
		template<typename MODULE>
		MODULE*	registerModule()
		{
			MODULE* mod = new MODULE();
			SYS_VERIFY_RV(mod != nullptr, nullptr);

			std::string name = typeid(MODULE).name();
			SYS_VERIFY_RV(registerModule(name, mod) != nullptr, nullptr);

			return mod;
		}

		/*获取注册的模块*/
		template<typename MODULE>
		MODULE*	getModule()
		{
			return dynamic_cast<MODULE*>(getModule(typeid(MODULE).name()));
		}

		IModule*	getModule(std::string name);
		/*注册模块，order决定模块initialize的调用顺序*/
		IModule*	registerModule(std::string name, IModule* module);

		bool initialize();
		void finalize();

		void preStartLoop();

	private:
		// 注册的所有模块
		std::map<std::string, IModule*>	mModules;
		std::vector<IComponentMgr*>	mComponentMgrs;
	};
}

#endif