/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "Config.h"

using namespace ff;

void Config::set(const std::string& key, const std::string& val)
{
	mValues[key] = val;
}

std::string Config::get(const std::string& key)
{
	std::map<std::string, std::string>::iterator iter = mValues.find(key);
	if (iter == mValues.end())
	{
		return "";
	}

	return iter->second;
}
