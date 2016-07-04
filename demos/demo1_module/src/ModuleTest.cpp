/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleTest.h"
#include "base.h"


using namespace ff::demo;

bool ModuleTest::initialize()
{
	SYSLOG_DEBUG("ModuleTest initialize.");
	return true;
}

void ModuleTest::finalize()
{
	SYSLOG_DEBUG("ModuleTest finalize.");
}
