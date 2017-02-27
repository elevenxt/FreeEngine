

#include "CfgIni.h"

using namespace ff;

bool CfgIni::load(std::string sfile)
{
	if (mIniParser != nullptr)
	{
		mMapValues.clear();
	}

	mIniParser = iniparser_load(sfile.c_str());
	return mIniParser != nullptr;
}

std::string CfgIni::getValue(std::string section, std::string key)
{
	std::string strComKey = section + std::string(":") + key;
	std::map<std::string, std::string>::iterator iter = mMapValues.find(strComKey);
	if (iter != mMapValues.end())
	{
		return iter->second;
	}
	
	if (mIniParser == nullptr)
	{
		return "";
	}

	std::string strVal = iniparser_getstring(mIniParser, strComKey.c_str(), "");
	mMapValues[strComKey] = strVal;
	return strVal;
}

void CfgIni::setValue(std::string section, std::string key, std::string value)
{
	std::string strComKey = section + std::string(":") + key;
	mMapValues[strComKey] = value;
}
