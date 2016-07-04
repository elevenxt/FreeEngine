/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_ACTORMGR_
#define _US_ACTORMGR_

#include <cinttypes>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <memory>

#include "Singleton.h"
#include "Actor.h"
#include "ActorWork.h"
#include "IModule.h"
#include "ComponentTick.h"

namespace ff
{
	class ModuleActor : public IModule, public ComponentTick
	{
	public:
		virtual bool initialize();
		virtual	void finalize();

		bool	registerActor(const std::string& name, Actor* actor);
		bool	dispatchWork(const std::string& name, ActorWork* work);

	public:
		void	poolActorWork();
		virtual int64_t loopTick(int64_t delta);

	private:
		struct ActorPeer
		{
			bool running;
			Actor* actor;
			std::thread worker;
		};
		static int32_t	actor_worker(ModuleActor::ActorPeer* act);

		struct ActorGroup
		{
			int32_t dispatchidx;
			std::vector<ActorPeer*> actors;
		};

		std::map<std::string, ActorGroup>		mActors;
	};
}

#endif