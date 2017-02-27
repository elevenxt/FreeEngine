

#include "base.h"
#include "ModuleRocksDb.h"

std::string kDBPath = "game.db";

using namespace ff;

bool ModuleRocksDb::initialize(ff::ModuleMgr& mgr)
{
	rocksdb::Options options;
	// create the DB if it's not already present
	options.create_if_missing = true;

	// open DB
	rocksdb::Status s = rocksdb::DB::Open(options, kDBPath, &mDb);
	if (!s.ok())
	{
		SYSLOG_ERROR(s.ToString());
		return false;
	}

	return true;
}

void ModuleRocksDb::finalize()
{
	delete mDb;
	mDb = nullptr;
}

std::string ModuleRocksDb::load(std::string key)
{
	std::string value;
	// get value
	rocksdb::Status s = mDb->Get(rocksdb::ReadOptions(), key, &value);
	return value;
}

void ModuleRocksDb::save(std::string key, std::string val)
{
	rocksdb::Status s = mDb->Put(rocksdb::WriteOptions(), key, val);
	SYS_VERIFY_R(s.ok());
}
