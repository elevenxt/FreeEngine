/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ComponentTick.h"
#include "base.h"

using namespace ff;

void ComponentTickMgr::tick(int32_t delta)
{
	for (ComTicker& ticker : mTickers)
	{
		ticker.left -= delta;
		if (ticker.left > 0)
		{
			continue;
		}
		ticker.gap = ticker.ticker->loopTick(ticker.gap - ticker.left);
		ticker.left = ticker.gap;
	}
}

bool ComponentTickMgr::registerModule(std::string name, IModule* module)
{
	ComponentTick* ticker = dynamic_cast<ComponentTick*>(module);
	if (ticker == nullptr)
	{
		return false;
	}

	mTickers.push_back({ ticker, 0 });
	SYSLOG_TRACE("find tick component {}.", name);

	return true;
}

bool ComponentTickMgr::initialize()
{
	return true;
}

void ComponentTickMgr::finalize()
{
	mTickers.clear();
}