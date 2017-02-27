
#include "CardGameLogicPlugin.h"
#include "ModuleShop.h"
#include "ModulePackHero.h"
#include "HotSwapServiceProxy.h"
#include "ModuleBattle.h"
#include "ModuleTalk.h"
#include "ModuleFriend.h"

using namespace ff;

static CardGameLogicPlugin sPlugin;

CardGameLogicPlugin::CardGameLogicPlugin()
{

}

CardGameLogicPlugin::~CardGameLogicPlugin()
{

}

HotSwapPlugin*	getPlugin()
{
	return &sPlugin;
}

bool CardGameLogicPlugin::init(HotSwapService* serve)
{
	mServe = serve;
	HotSwapServiceProxy::instance().reset(mServe);

	mModuleMsgTrigger = new ModuleMsgTrigger();
	mServe->registerModule(typeid(ModuleMsgTrigger).name(), mModuleMsgTrigger);
	mServe->registerModule(typeid(ModuleShop).name(), new ModuleShop());
	mServe->registerModule(typeid(ModulePackHero).name(), new ModulePackHero());
	mServe->registerModule(typeid(ModuleBattle).name(), new ModuleBattle());
	mServe->registerModule(typeid(ModuleTalk).name(), new ModuleTalk());
	mServe->registerModule(typeid(ModuleFriend).name(), new ModuleFriend());

	mServe->init();
	return true;
}

void CardGameLogicPlugin::unit()
{
	mServe->uninit();
}


int32_t CardGameLogicPlugin::netMsg(Player& player, int32_t msgid, const char* msg, int32_t len)
{
	return mModuleMsgTrigger->triggerNetMsg(player, msgid, msg, len);
}