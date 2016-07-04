/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleTest2.h"
#include "ModuleMgr.h"
#include "base.h"


using namespace ff::demo;

bool ModuleTest2::initialize()
{
	mModuleTest3 = ff::ModuleMgr::instance().getModule<ModuleTest3>();
	SYSLOG_DEBUG("ModuleTest initialize.");
	return true;
}

void ModuleTest2::finalize()
{
	SYSLOG_DEBUG("ModuleTest finalize.");
}

void ModuleTest2::hello()
{
	SYSLOG_DEBUG("ModuleTest2 hello.");
	/*调用模块3的函数hello*/
	mModuleTest3->hello();
}