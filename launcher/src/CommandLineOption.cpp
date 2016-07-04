/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "CommandLineOption.h"
#include "base.h"

using namespace ff;


void CommandLineOption::setOption(const std::string& name, bool required)
{
	mRequired[name] = required;
}

bool CommandLineOption::parse(int32_t num, char* args[])
{
	for (int32_t i = 0; i < num; i++)
	{
		std::string arg = std::string(args[i]);
		if (arg.size() != 2 || arg[0] != '-')
		{
			continue;
		}
		std::string option = "0";
		option[0] = arg[1];

		mOptions[option] = "";
		if (i<num-1 && !isOption(args[i+1]))
		{
			mOptions[option] = args[i + 1];
		}
	}

	for (std::map<std::string, bool>::iterator iter = mRequired.begin();
		iter != mRequired.end(); ++iter)
	{
		if (iter->second && mOptions.find(iter->first) == mOptions.end())
		{
			printf("required option -%s not found.", iter->first.c_str());
			return false;
		}
	}

	return true;
}

bool CommandLineOption::isSet(const std::string& name)
{
	return mOptions.find(name) != mOptions.end();
}

std::string CommandLineOption::getOption(const std::string& name)
{
	return mOptions[name];
}

bool CommandLineOption::isOption(const std::string& val)
{
	return val.size() == 2 && val[0] == '-';
}