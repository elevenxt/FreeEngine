/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_NETSERVICE_
#define _US_NETSERVICE_

#include <string>
#include <vector>
#include <set>
#include <map>

#include "ut_net_package.h"
#include "ut_net_listener.h"
#include "NetPeer.h"

namespace ff
{
	class NetService
	{
	public:
		class Listener
		{
		public:
			virtual void newconn(NetService*, int32_t) = 0;
			virtual void lostconn(NetService*, int32_t) = 0;
			virtual void recvdata(NetService*, int32_t, const char*, int32_t) = 0;
		};

		NetService();
		~NetService();

	public:
		bool init(Listener* listener, int32_t connlimit);
		void uninit();
		bool createListener(const std::string& ip, int32_t port);
		bool connect(const std::string& ip, int32_t port);
		void poolOnce(int32_t weight, int32_t waittime);
		void close(int32_t idx);
		bool send(int32_t idx, const std::string& data);
		bool send(int32_t idx, const char* data, int dlen);

	private:
		static void newconnection(struct ut_pkgchannel_t* channel, void* netdata, void* channeldata);
		static void lostconnection(struct ut_pkgchannel_t* channel, void* netdata, void* channeldata);
		static void recvdata(struct ut_pkgchannel_t* channel, const char* data
			, int32_t datalen, void* netdata, void* channeldata);

	private:
		struct ut_pkgnet_t*	mNet;
		std::vector<ut_pkgchannel_t*>		mChannels;
		std::vector<NetPeer>	mListeners;
		Listener* mEventListener;
	};	
}

#endif
