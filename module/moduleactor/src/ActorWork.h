/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_ACTOR_WORK_
#define _US_ACTOR_WORK_

#include <functional>
#include <cinttypes>

namespace ff
{
	class ActorWork
	{
	public:
		virtual ~ActorWork(){};
		void setCallback(std::function<void(ActorWork*)> callback, int32_t timeout);
		void doCallback();

	private:
		int32_t								mTimeout;
		int32_t								mTimeLeft;
		std::function<void(ActorWork*)> mCallback;
	};
}
#endif