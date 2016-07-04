/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_VALUEOPT_
#define _US_VALUEOPT_

#include <sstream>
#include <cinttypes>

namespace ff
{
	// 基本类型转换
	class ValueOpt
	{
	public:
		template<typename T>
		static std::string	convert(T t)
		{
			std::ostringstream os;
			os << t;
			return os.str();
		}

		template<typename T>
		static T convert(std::string str)
		{
			T t{};
			std::istringstream is(str);
			is >> t;
			return t;
		}

		static std::string convert(const std::string& str)
		{
			return str;
		}
	};
}

#endif