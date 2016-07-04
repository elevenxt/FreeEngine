/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ModuleActor.h"
#include "Timer.h"
#include "base.h"

using namespace ff;

bool ModuleActor::initialize()
{
	return true;
}

void ModuleActor::finalize()
{

}

int32_t	ModuleActor::actor_worker(ModuleActor::ActorPeer* act)
{
	SYS_VERIFY_RV(act != nullptr && act->actor != nullptr, 0xdead);

	Actor* actor = act->actor;
	int64_t bt = Timer::getTickCount();
	while (act->running)
	{
		int64_t et = Timer::getTickCount();
		int64_t delta = et - bt;
		bt = et;
		
		int64_t sleept = actor->loopProcess(delta);
		if (sleept > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleept));
		}		
	}

	return 0;
}

bool	ModuleActor::registerActor(const std::string& name, Actor* actor)
{
	SYS_VERIFY_RV(actor != nullptr, false);
	ActorGroup& actGroup = mActors[name];
	

	ActorPeer* act = new ActorPeer();
	SYS_VERIFY_RV(act != nullptr, false);

	act->running = true;
	act->actor = actor;
	act->worker = std::thread(std::bind(ModuleActor::actor_worker, act));

	actGroup.actors.push_back(act);

	return true;
}

bool	ModuleActor::dispatchWork(const std::string& name, ActorWork* work)
{
	SYS_VERIFY_RV(work != nullptr, false);
	ActorGroup& actGroup = mActors[name];
	SYS_VERIFY_RV(!actGroup.actors.empty(), false);

	actGroup.dispatchidx = (actGroup.dispatchidx + 1) % actGroup.actors.size();
	actGroup.actors[actGroup.dispatchidx]->actor->dispatchWork(work);

	return true;
}

void	ModuleActor::poolActorWork()
{
	for (std::map<std::string, ActorGroup>::iterator iter = mActors.begin();
		iter != mActors.end(); ++iter)
	{
		ActorGroup& actorGroup = iter->second;
		for (std::vector<ActorPeer*>::iterator aiter = actorGroup.actors.begin();
			aiter != actorGroup.actors.end(); ++aiter)
		{
			(*aiter)->actor->poolActorWork();
		}
	}
}

int64_t ModuleActor::loopTick(int64_t delta)
{
	poolActorWork();
	return 1;
}