/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "NetService.h"
#include "base.h"
#include "StringUtil.h"
#include "ValueOpt.h"

using namespace ff;

NetService::NetService()
{
	mNet = nullptr;
}

NetService::~NetService()
{
	uninit();
}

void NetService::newconnection(struct ut_pkgchannel_t* channel, void* netdata, void* channeldata)
{
	int32_t cidx = ut_pkgnet_channel_index(channel);
	NetService* service = (NetService*)netdata;
	SYS_VERIFY_R(service != nullptr && cidx >= 0 && cidx < (int32_t)service->mChannels.size() && service->mChannels[cidx] == nullptr);
	service->mChannels[cidx] = channel;

	if (channeldata != nullptr)
	{
		NetPeer* connect = (NetPeer*)channeldata;
		SYS_VERIFY_R(connect->mIdx == -1 && connect->mSock != ut_sock_invalid());
		connect->mIdx = cidx;
		SYSLOG_DEBUG("new connection [] made.", connect->mName);
	}

	SYS_VERIFY_R(service->mEventListener != nullptr);
	service->mEventListener->newconn(service, cidx);
}

void NetService::lostconnection(struct ut_pkgchannel_t* channel, void* netdata, void* channeldata)
{
	int32_t cidx = ut_pkgnet_channel_index(channel);
	NetService* service = (NetService*)netdata;
	SYS_VERIFY_R(service != nullptr && cidx >= 0 && cidx < (int32_t)service->mChannels.size() && service->mChannels[cidx] != nullptr);

	SYS_VERIFY_R(service->mEventListener != nullptr);
	service->mEventListener->lostconn(service, cidx);

	service->mChannels[cidx] = nullptr;
	if (channeldata != nullptr)
	{
		NetPeer* connect = (NetPeer*)channeldata;
		SYS_VERIFY_R(connect->mIdx != -1 && connect->mSock != ut_sock_invalid());
		connect->mIdx = -1;
		connect->mSock = ut_sock_invalid();
		SYSLOG_DEBUG("lost connection [].", connect->mName);
	}
}

void NetService::recvdata(struct ut_pkgchannel_t* channel, const char* data
	, int32_t datalen, void* netdata, void* channeldata)
{
	int32_t cidx = ut_pkgnet_channel_index(channel);
	NetService* service = (NetService*)netdata;
	SYS_VERIFY_R(service != nullptr && cidx >= 0 && cidx < (int32_t)service->mChannels.size() && service->mChannels[cidx] != nullptr);

	SYS_VERIFY_R(service->mEventListener != nullptr);
	service->mEventListener->recvdata(service, cidx, data, datalen);
}

bool NetService::init(Listener* listener, int32_t connlimit)
{
	mEventListener = listener;
	SYS_VERIFY_RV(mEventListener != nullptr, false);
	SYS_VERIFY_RV(mNet == nullptr, false);
	ut_pkgnet_config_t* cfg = ut_pkgnet_config_create();
	SYS_VERIFY_RV(cfg != 0, false);
	ut_pkgnet_config_set_connectionlimit(cfg, connlimit);
	ut_pkgnet_config_set_maxpackage(cfg, 1024);
	mNet = ut_pkgnet_create(cfg, newconnection, lostconnection, this);

	mChannels.resize(connlimit);

	return mNet != nullptr;
}

void NetService::uninit()
{
	if (mNet == nullptr)
	{
		return;
	}

	ut_pkgnet_delete(mNet);
	mNet = nullptr;
}

bool NetService::createListener(const std::string& ip, int32_t port)
{
	ut_sock_t listener = ut_net_open_listener(ip.c_str(), port);
	if (!ut_sock_isvalidate(listener))
	{
		return false;
	}

	NetPeer peer;
	peer.mAddress = NetAddress(ip, port);
	peer.mSock = listener;
	mListeners.push_back(peer);

	SYSLOG_NOTICE("net listen on [{}:{}].", ip, port);

	return true;
}

bool NetService::connect(const std::string& ip, int32_t port)
{
	ut_sock_t tcpsock = ut_sock_tcp();
	if (0 != ut_sock_connect(tcpsock, ip.c_str(), port))
	{
		ut_sock_close(tcpsock);
		return false;
	}

	return 0 != ut_pkgnet_deliver_socket(mNet, tcpsock, recvdata, 0);
}

void NetService::poolOnce(int32_t weight, int32_t waittime)
{
	if (weight < 16)
	{
		weight = 16;
	}

	for (std::vector<NetPeer>::iterator iter = mListeners.begin();
		iter != mListeners.end(); ++iter)
	{
		for (int i = 0; i < weight / 4; i++)
		{
			ut_sock_t newsock = ut_net_accept_newsock(iter->mSock);
			if (!ut_sock_isvalidate(newsock))
			{
				break;
			}

			ut_pkgnet_deliver_socket(mNet, newsock, recvdata, 0);
		}
	}

	ut_pkgnet_pool_once(mNet, weight, waittime);
}

void NetService::close(int32_t idx)
{
	SYS_VERIFY_R(idx >= 0 && idx < (int32_t)mChannels.size());
	if (mChannels[idx] != nullptr)
	{
		ut_pkgnet_channel_close(mChannels[idx]);
	}
}

bool NetService::send(int32_t idx, const std::string& data)
{
	SYS_VERIFY_RV(idx >= 0 && idx < (int32_t)mChannels.size(), false);
	if (mChannels[idx] != nullptr)
	{
		return 0 == ut_pkgnet_send(mChannels[idx], data.c_str(), data.size());
	}
	return false;
}

bool NetService::send(int32_t idx, const char* data, int dlen)
{
	SYS_VERIFY_RV(idx >= 0 && idx < (int32_t)mChannels.size(), false);
	if (mChannels[idx] != nullptr)
	{
		return 0 == ut_pkgnet_send(mChannels[idx], data, dlen);
	}
	return false;
}