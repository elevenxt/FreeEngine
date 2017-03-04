

#include <memory>

#include "CfgIni.h"
#include "StringUtil.h"
#include "ModuleHotSwap.h"
#include "base.h"
#include "ValueOpt.h"
#include "cfg_loader.h"
#include "ReloadMgr.h"
#include "ReloadCfg.h"
#include "ReloadLogicPlugin.h"
#include "HotSwapPluginProxy.h"

using namespace ff;

bool ModuleHotSwap::initialize(ff::ModuleMgr& mgr)
{
	std::string cfgFile = CfgIni::instance().get<std::string>("data", "file");
	std::string logicFile = CfgIni::instance().get<std::string>("hslogic", "file");
	// 策划配置的热更
	ReloadMgr::instance().addReloadable(std::shared_ptr<ReloadCfg>(new ReloadCfg(cfgFile)));
	// 游戏逻辑的热更
	ReloadMgr::instance().addReloadable(std::shared_ptr<ReloadLogicPlugin>(new ReloadLogicPlugin(logicFile)));
	// 首次运行时，主动加载一次
	ReloadMgr::instance().makeReload();
	ReloadMgr::instance().confirmReload();

	// 加查一下逻辑模块是否准备就绪
	SYS_VERIFY_RV(HotSwapPluginProxy::instance().good(), false);

	return true;
}

void ModuleHotSwap::finalize()
{

}

int32_t ModuleHotSwap::runOnce()
{
	ReloadMgr::instance().makeReload();

	return 1000;
}

int64_t ModuleHotSwap::loopTick(int64_t delta)
{
	ReloadMgr::instance().confirmReload();

	return 1000;
}

