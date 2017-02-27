
#ifndef _FF_CONFIG_INI_
#define _FF_CONFIG_INI_

#include <string>
#include <map>

#include "Singleton.h"
#include "iniparser.h"
#include "ValueOpt.h"

namespace ff
{
	/**
	* ini格式的配置文件读取
	*/
	class CfgIni : public Singleton<CfgIni>
	{
	public:
		bool load(std::string sfile);
		std::string getValue(std::string section, std::string key);
		void setValue(std::string section, std::string key, std::string value);

		template<typename T>
		T get(std::string section, std::string key)
		{
			std::string strv = getValue(section, key);
			return ValueOpt::convert<T>(strv);
		}

		template<typename T>
		void set(std::string section, std::string key, T value)
		{
			std::string strVal = ValueOpt::convert(value);
			setValue(section, key, strVal);
		}

	private:
		dictionary*	mIniParser = nullptr;
		std::map<std::string, std::string> mMapValues;
	};
}

#endif