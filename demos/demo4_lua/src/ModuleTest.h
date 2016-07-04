/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_TEST_
#define _US_MODULE_TEST_

#include <string>

#include "IModule.h"


namespace ff
{
	namespace demo
	{
		class ModuleTest : public ff::IModule
		{
		public:
			virtual bool initialize();
			virtual	void finalize();
			virtual void preStartLoop();

		private:
			int32_t testFunc1(int32_t a, int32_t b);
			std::string testFunc2(std::string a, std::string b);
		};
	}
}

#endif
