/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleTest3.h"
#include "base.h"


using namespace ff::demo;

bool ModuleTest3::initialize()
{
	SYSLOG_DEBUG("ModuleTest initialize.");
	return true;
}

void ModuleTest3::finalize()
{
	SYSLOG_DEBUG("ModuleTest finalize.");
}

void ModuleTest3::hello()
{
	SYSLOG_DEBUG("ModuleTest3 hello.");
}