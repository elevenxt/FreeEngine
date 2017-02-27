

#include <fstream>
#include "Reloadable.h"
#include "ut_file.h"

namespace ff {

	Reloadable::Reloadable(std::string fname)
	{
		mFileName = fname;
		mWriteTime = 0;
	}

	bool Reloadable::tryReload()
	{
		// 加查文件修改时间，修改时间变化时才进行热替换
		int64_t nCurWriteTime = ut_file_modifytime(mFileName.c_str());
		if (nCurWriteTime == mWriteTime)
		{
			return false;
		}

		// 尝试打开文件，如果打开失败则不能进行热加载
		std::ifstream ifile(mFileName, std::ios::binary);
		if (!ifile.good()) {
			return false;
		}
		ifile.close();

		// 加载进内存，准备进行热替换
		if (!doReload())
		{
			return false;
		}

		mWriteTime = nCurWriteTime;
		return true;
	}
}