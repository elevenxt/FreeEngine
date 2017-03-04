
#include <cinttypes>
#include <chrono>
#include "CfgIni.h"
#include "ReloadLogicPlugin.h"
#include "HotSwapServiceImpl.h"
#include "HotSwapPluginProxy.h"
#include "base.h"


using namespace ff;

ReloadLogicPlugin::PluginData::PluginData()
{
	plugin = nullptr;
	service = nullptr;
	dll_handle = 0;
}

ReloadLogicPlugin::PluginData::~PluginData()
{
	if (plugin != nullptr)
	{
		plugin->unit();
	}
	delete service;
	if (dll_handle != 0)
	{
		ut_dll_close(dll_handle);
	}
}

static bool copyFile(const char *srcFile, const char *dstPath)
{
	static const int32_t BUFFER_SIZE = 4096;
	FILE *fpR, *fpW;
	char buffer[BUFFER_SIZE];
	int32_t lenR, lenW;
	if ((fpR = fopen(srcFile, "rb")) == NULL)
	{
		SYSLOG_WARNING("open read file {} failed.", srcFile);
		return false;
	}
	if ((fpW = fopen(dstPath, "wb")) == NULL)
	{
		SYSLOG_WARNING("open write file {} failed.", dstPath);
		fclose(fpR);
		return false;
	}

	memset(buffer, 0, BUFFER_SIZE);
	while ((lenR = fread(buffer, 1, BUFFER_SIZE, fpR)) > 0)
	{
		if ((lenW = fwrite(buffer, 1, lenR, fpW)) != lenR)
		{
			fclose(fpR);
			fclose(fpW);
			SYSLOG_WARNING("write file {} failed.", dstPath);
			return false;
		}
		memset(buffer, 0, BUFFER_SIZE);
	}

	fclose(fpR);
	fclose(fpW);
	return true;
}

ReloadLogicPlugin::ReloadLogicPlugin(std::string fname) : ff::Reloadable(fname)
{
	mPlugin = nullptr;
	mNewPlugin = nullptr;
}

bool ReloadLogicPlugin::doReload()
{
	if (mNewPlugin != nullptr)
	{
		return false;
	}

	std::string dstDir = CfgIni::instance().get<std::string>("hslogic", "tmpdir");
	auto now = std::chrono::system_clock::now();
	time_t tt;
	tt = std::chrono::system_clock::to_time_t(now);
	std::string tmpName = dstDir + ValueOpt::convert(tt) + ValueOpt::convert(rand()) + "_tmpplugin.dll";
	if (!copyFile(mFileName.c_str(), tmpName.c_str()))
	{
		SYSLOG_WARNING("copy file from {} to {} failed.", mFileName, tmpName);
		return false;
	}

	mNewPlugin = loadPlugin(tmpName);
	return true;
}

void ReloadLogicPlugin::confirmReload()
{
	if (mNewPlugin == nullptr)
	{
		return;
	}

	delete mPlugin;
	mPlugin = mNewPlugin;
	mNewPlugin = nullptr;

	HotSwapPluginProxy::instance().reset(mPlugin->plugin);
}

ReloadLogicPlugin::PluginData* ReloadLogicPlugin::loadPlugin(std::string dllname)
{
	PluginData* pData = new PluginData();
	pData->fname = dllname;
	pData->dll_handle = ut_dll_load(pData->fname.c_str());
	do {
		if (pData->dll_handle == 0)
		{
			SYSLOG_ERROR(fmt::format("dll load failed {}.", pData->fname));
			break;
		}
		GetPlugin gplugin = (GetPlugin)ut_dll_access(pData->dll_handle, "getPlugin");
		if (gplugin == nullptr)
		{
			SYSLOG_ERROR(fmt::format("dll {} do not has global c func getPlugin.", pData->fname));
			break;
		}
		pData->plugin = gplugin();
		if (pData->plugin == nullptr)
		{
			SYSLOG_ERROR(fmt::format("plugin {} load failed", mPluginDllFile));
			break;
		}
		pData->service = new HotSwapServiceImpl();
		if (!pData->plugin->init(pData->service)) {
			SYSLOG_ERROR(fmt::format("plugin {} init failed", mPluginDllFile));
			break;
		}

		return pData;
	} while (false);

	delete pData;
	return nullptr;
}