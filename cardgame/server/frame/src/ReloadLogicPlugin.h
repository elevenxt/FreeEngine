/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_RELOADABLE_LOGICPLUGIN_
#define _FF_RELOADABLE_LOGICPLUGIN_

#include <string>

#include "Reloadable.h"
#include "ut_dll.h"
#include "HotSwapPlugin.h"

namespace ff
{
	class ReloadLogicPlugin : public Reloadable
	{
	public:
		ReloadLogicPlugin(std::string fname);
		virtual bool doReload();
		virtual void confirmReload();

	private:
		struct PluginData
		{
			PluginData();
			~PluginData();
			std::string fname;
			HotSwapPlugin* plugin;
			HotSwapService* service;
			dll_handle_t dll_handle;
		};	
	private:
		PluginData* loadPlugin(std::string dllname);

	private:
		std::string mPluginDllFile;
		std::string mPluginDllTmpDir;
		PluginData*	mPlugin;
		PluginData* mNewPlugin;
	};
}

#endif