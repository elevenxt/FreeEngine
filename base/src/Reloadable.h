/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_RELOADABLE_
#define _FF_RELOADABLE_

#include <string>
#include <cinttypes>


namespace ff
{
	class Reloadable
	{
	public:
		Reloadable(std::string fname);
		bool tryReload();

		virtual bool doReload() = 0;
		virtual void confirmReload() = 0;

	protected:
		std::string mFileName;
		int64_t mWriteTime;
	};
}

#endif