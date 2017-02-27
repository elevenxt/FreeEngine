#include "ModuleLuaExport.h"
#include "LuaExportFuncs.h"

#include "ModuleMgr.h"

using namespace ff;

bool ModuleLuaExport::initialize(ModuleMgr& mgr)
{
	// ×¢²áÈÕÖ¾º¯Êý
	LuaExportFuncs::instance().registerFunc("log.trace", SyslogTrace);
	LuaExportFuncs::instance().registerFunc("log.debug", SyslogDebug);
	LuaExportFuncs::instance().registerFunc("log.notice", SyslogNotice);
	LuaExportFuncs::instance().registerFunc("log.warn", SyslogWarning);
	LuaExportFuncs::instance().registerFunc("log.error", SyslogError);

	return true;
}

void ModuleLuaExport::finalize()
{
	
}