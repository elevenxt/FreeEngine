
#include <fstream>
#include <string>
#include <vector>

#include "CfgIni.h"
#include "ReloadCfg.h"
#include "StringUtil.h"
#include "base.h"
#include "cfg_loader.h"


using namespace ff;

bool ReloadCfg::doReload()
{
	std::string cfgFile = CfgIni::instance().get<std::string>("data", "file");
	std::ifstream ifile(cfgFile, std::ios_base::in | std::ios_base::binary);
	std::streampos pos = ifile.tellg(); 
	ifile.seekg(0, std::ios::end);
	int32_t len = ifile.tellg();
	ifile.seekg(pos);
	char* bufdata = new char[len + 1];
	ifile.read(bufdata, len);
	bufdata[len] = 0;

	std::vector<std::string> fc = ff::StringUtil::split(bufdata, "^");
	delete[] bufdata;

	for (int32_t i = 0; i < (int32_t)fc.size() / 2; i++)
	{
		std::string name = fc[i * 2];
		std::string content = fc[i * 2 + 1];

		std::vector<std::string> line = StringUtil::split(content, "$");
		std::vector<std::vector<std::string>> rows;
		for (std::string& row : line)
		{
			if (row.empty())
			{
				continue;
			}
			rows.push_back(StringUtil::split(row, "#"));
		}

		SYS_CHECK_RV(cfg_loader::reload(name, rows), false);
	}

	return true;
}

void ReloadCfg::confirmReload()
{
	cfg_mgr_impl::instance().trychangecfg();
}