/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_RELOADMGR_
#define _FF_RELOADMGR_

#include <vector>
#include <string>
#include <memory>

#include "Reloadable.h"
#include "Singleton.h"


namespace ff
{
	class ReloadMgr : public Singleton<ReloadMgr>
	{
	public:
		bool addReloadable(std::shared_ptr<Reloadable> item);
		void makeReload();
		void confirmReload();

	private:
		std::vector<std::shared_ptr<Reloadable>> mReloadables;
	};
}

#endif