/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_LUAVAR_
#define _US_MODULE_LUAVAR_

#include "IModule.h"

namespace ff
{
	class ModuleLuaVar : public IModule
	{
	public:
		virtual bool initialize();
		virtual	void finalize();
	};
}

#endif
