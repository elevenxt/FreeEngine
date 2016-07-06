/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "Spinlock.h"
#include <cassert>

using namespace ff;

Spinlock::Spinlock()
{
	mValue = std::shared_ptr<std::atomic<int32_t>>(new std::atomic<int32_t>(0));
}

bool Spinlock::isValidate()
{
	return mValue != nullptr;
}

bool Spinlock::trylock()
{
	if (!isValidate())
	{
		return false;
	}
	return mValue->exchange(1) == 0;
}

void Spinlock::lock()
{
	if (!isValidate())
	{
		assert(false);
		return;
	}
	while (mValue->exchange(1) == 1);
}

void Spinlock::unlock()
{
	if (!isValidate())
	{
		assert(false);
		return;
	}
	mValue->store(0);
}