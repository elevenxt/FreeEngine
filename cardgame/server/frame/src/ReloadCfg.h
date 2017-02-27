/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_RELOADABLE_CFG_
#define _FF_RELOADABLE_CFG_

#include "Reloadable.h"

namespace ff
{
	class ReloadCfg : public Reloadable
	{
	public:
		ReloadCfg(std::string fname) : Reloadable(fname) {}
		virtual bool doReload();
		virtual void confirmReload();
	};
}

#endif