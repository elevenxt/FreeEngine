/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_MODULE_ROCKSDB_
#define _US_MODULE_ROCKSDB_


#include <string>
#include <cinttypes>

#include "IModule.h"
#include "rocksdb/db.h"

namespace ff
{
	class ModuleRocksDb : public IModule
	{
	public:
		virtual bool initialize(ff::ModuleMgr& mgr);
		virtual	void finalize();

		std::string load(std::string key);
		void save(std::string key, std::string val);

	private:
		rocksdb::DB*	mDb;
	};
}
#endif