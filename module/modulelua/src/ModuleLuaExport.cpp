#include "ModuleLuaExport.h"
#include "LuaExportFuncs.h"

#include "ModuleMgr.h"
#include "ModuleNetService.h"
#include "NetService.h"

using namespace ff;

bool ModuleLuaExport::initialize()
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