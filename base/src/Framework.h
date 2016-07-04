/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_FRAMEWORK_H_
#define _US_FRAMEWORK_H_

#include <vector>
#include <map>
#include <string>

#include "IModule.h"

namespace ff
{
	/*
		Æô¶¯¿ò¼Ü
	*/
	class Framework
	{
	public:
		Framework();
		virtual ~Framework();
		static Framework* instance();

		bool doInit();
		void doUninit();
		void startLoop();

	protected:
		virtual bool initialize() = 0;
		virtual void finalize() = 0;
	};
}

#endif