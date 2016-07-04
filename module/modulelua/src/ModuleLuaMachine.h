/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_MODULE_LUAMACHINE_
#define _US_MODULE_LUAMACHINE_

#include "IModule.h"
#include "ComponentTick.h"

namespace ff
{
	class ModuleLuaMachine : public IModule, public ComponentTick
	{
	public:
		virtual bool initialize();
		virtual	void finalize();
		virtual void preStartLoop();

		bool reloadLuaMachine();
		bool initLuaMachine(std::string entry);	

	protected:
		virtual int64_t loopTick(int64_t delta);
		std::string mEntry;
	};
}

#endif
