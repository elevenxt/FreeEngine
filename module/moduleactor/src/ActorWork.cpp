/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "ActorWork.h"

using namespace ff;

void ActorWork::setCallback(std::function<void(ActorWork*)> callback, int32_t timeout)
{
	mCallback = callback;
	mTimeout = timeout;
	mTimeLeft = timeout;
}

void ActorWork::doCallback()
{
	if (mCallback)
	{
		mCallback(this);
	}
}