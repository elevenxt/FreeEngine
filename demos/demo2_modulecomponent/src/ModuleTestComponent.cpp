/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleTestComponent.h"
#include "base.h"


using namespace ff::demo;
using namespace ff;

bool ModuleTestComponent::initialize(ModuleMgr& mgr)
{
	mTick = 0;
	SYSLOG_DEBUG("ModuleTestComponent initialize.");
	return true;
}

void ModuleTestComponent::finalize()
{
	SYSLOG_DEBUG("ModuleTestComponent finalize.");
}

int64_t ModuleTestComponent::loopTick(int64_t delta)
{
	mTick++;
	SYSLOG_DEBUG("{} ModuleTestComponent hello tick.", mTick);
	return 1000;
}