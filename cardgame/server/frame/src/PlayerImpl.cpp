
#include "PlayerImpl.h"

using namespace ff;

PlayerImpl::PlayerImpl(NetService* netService, int32_t netid)
{
	mNetService = netService;
	mNetId = netid;
}

void PlayerImpl::disconnect()
{
	mNetService->close(mNetId);
}

bool PlayerImpl::send(const char* data, int32_t len)
{
	return mNetService->send(mNetId, data, len);
}

bool PlayerImpl::isLogined()
{
	return mLogined;
}

PlayerData& PlayerImpl::data()
{
	return mData;
}

void PlayerImpl::setLogined(bool logined)
{
	mLogined = logined;
}

PlayerDataImpl& PlayerImpl::dataImpl()
{
	return mData;
}

int32_t PlayerImpl::getNetId()
{
	return mNetId;
}