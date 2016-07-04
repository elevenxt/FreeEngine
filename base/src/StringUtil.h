/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _UTS_STRINGUTIL_
#define _UTS_STRINGUTIL_

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

namespace ff
{
	class StringUtil
	{
	public:
		// ×Ö·û´®ÇÐ·Ö
		static std::vector<std::string> split(const std::string& val, const std::string& spl);

		// ×Ö·û´®Ìæ»»
		static std::string replace(const std::string& str_src, const std::string& old_value, const std::string& new_value);
		// ×ª»»Îª´óÐ´
		static std::string toupper(const std::string& str);
		// ×ª»»ÎªÐ¡Ð´
		static std::string tolower(const std::string& str);

		// ×Ö·û´®Á¬½Ó
		template<typename Container>
		static std::string connect(Container value, const std::string &delim)
		{
			if (value.begin() == value.end())
			{
				return std::string();
			}

			std::stringstream ss;
			typename Container::iterator iter = value.begin();
			ss << *iter;
			++iter;
			for (; iter != value.end(); ++iter)
			{
				ss << delim << *iter;
			}
			return ss.str();
		}
		template<typename Container>
		static std::string connect(Container value, const std::string &delim, const std::string &before, const std::string &after)
		{
			if (value.begin() == value.end())
			{
				return std::string();
			}

			std::stringstream ss;
			typename Container::iterator iter = value.begin();
			ss << before << *iter << after;
			++iter;
			for (; iter != value.end(); ++iter)
			{
				ss << delim << before << *iter << after;
			}
			return ss.str();
		}

	};
}
#endif