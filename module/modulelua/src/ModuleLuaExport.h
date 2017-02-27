/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_LUAEXPORT_
#define _US_MODULE_LUAEXPORT_

#include "IModule.h"

namespace ff
{
	class ModuleLuaExport : public IModule
	{
	public:
		virtual bool initialize(ModuleMgr& mgr);
		virtual	void finalize();
	};
}

#endif
