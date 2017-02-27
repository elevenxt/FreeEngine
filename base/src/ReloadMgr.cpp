


#include "ReloadMgr.h"

using namespace ff;

bool ReloadMgr::addReloadable(std::shared_ptr<Reloadable> item)
{
	mReloadables.push_back(item);
	return true;
}

void ReloadMgr::makeReload()
{
	for (std::shared_ptr<Reloadable> ritem : mReloadables)
	{
		ritem->tryReload();
	}
}

void ReloadMgr::confirmReload()
{
	for (std::shared_ptr<Reloadable> ritem : mReloadables)
	{
		ritem->confirmReload();
	}
}