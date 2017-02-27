/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ComponentRunnable.h"
#include "base.h"

using namespace ff;

int32_t	ComponentRunnableMgr::worker(ComRunnable* com)
{
	while (com->running)
	{
		int64_t sleept = com->runnable->runOnce();
		if (sleept > 0 && com->running)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleept));
		}
	}

	return 0xdead;
}

void ComponentRunnableMgr::tick(int32_t delta)
{
}

bool ComponentRunnableMgr::registerModule(std::string name, IModule* module)
{
	ComponentRunnable* runnable = dynamic_cast<ComponentRunnable*>(module);
	if (runnable == nullptr)
	{
		return false;
	}
	
	ComRunnable* com = new ComRunnable();
	com->running = true;
	com->runnable = runnable;	
	mRunnables.push_back(com);

	SYSLOG_TRACE("find runnable component {}.", name);
	
	return true;
}

bool ComponentRunnableMgr::initialize()
{
	for (ComRunnable* com : mRunnables)
	{
		com->worker = std::thread(std::bind(ComponentRunnableMgr::worker, com));
	}

	return true;
}

void ComponentRunnableMgr::finalize()
{
	for (std::vector<ComRunnable*>::iterator iter = mRunnables.begin();
		iter != mRunnables.end(); ++iter)
	{
		ComRunnable* com = *iter;
		com->running = false;
		com->worker.join();
		delete com;
	}
	mRunnables.clear();
}