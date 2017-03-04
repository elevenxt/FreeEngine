

#include "HotSwapPluginProxy.h"

using namespace ff;

HotSwapPluginProxy::HotSwapPluginProxy()
{
	mImpl = nullptr;
}

bool HotSwapPluginProxy::good()
{
	return mImpl != nullptr;
}

void HotSwapPluginProxy::reset(HotSwapPlugin* impl)
{
	mImpl = impl;
}

bool HotSwapPluginProxy::init(HotSwapService* serve)
{
	return mImpl->init(serve);
}

void HotSwapPluginProxy::unit()
{
	mImpl->unit();
}

int HotSwapPluginProxy::netMsg(Player& player, int32_t msgid, const char* msg, int32_t len)
{
	SYS_CHECK_RV(player.isLogined(), -1);

	return mImpl->netMsg(player, msgid, msg, len);
}