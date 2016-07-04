/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_COMMANDLINE_OPTION_
#define _US_COMMANDLINE_OPTION_

#include <map>
#include <string>
#include <cinttypes>

namespace ff
{
	class CommandLineOption
	{
	public:
		void setOption(const std::string& name, bool required);
		bool parse(int32_t num, char* args[]);
		bool isSet(const std::string& name);
		std::string getOption(const std::string& name);

	private:
		bool isOption(const std::string& val);

	private:
		std::map<std::string, bool>		   mRequired;
		std::map<std::string, std::string> mOptions;
	};
}
#endif