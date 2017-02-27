

#ifndef _FF_CARDGAME_LOGINPLUGIN_
#define _FF_CARDGAME_LOGINPLUGIN_
#include <cinttypes>
#include "HotSwapPlugin.h"
#include "HotSwapService.h"
#include "ModuleMsgTrigger.h"
#include "Player.h"

namespace ff
{
	class CardGameLogicPlugin : public HotSwapPlugin
	{
	public:
		CardGameLogicPlugin();
		~CardGameLogicPlugin();

		virtual bool init(HotSwapService* serve);
		virtual void unit();
		virtual int32_t netMsg(Player& player, int32_t msgid, const char* msg, int32_t len);

	private:
		HotSwapService* mServe;
		ModuleMsgTrigger* mModuleMsgTrigger;
	};
}

extern "C"
{
	DLLExport ff::HotSwapPlugin*	getPlugin();
}

#endif


