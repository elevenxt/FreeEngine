/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_CONFIG_
#define _FF_CONFIG_

#include <map>
#include <string>

#include "Singleton.h"


namespace ff
{
	class Config : public Singleton<Config>
	{
	public:
		void set(const std::string& key, const std::string& val);
		std::string get(const std::string& key);

	private:
		std::map<std::string, std::string> mValues;
	};
}
#endif