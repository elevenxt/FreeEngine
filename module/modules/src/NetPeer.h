/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _US_NETCONNECT_
#define _US_NETCONNECT_

#include <string>

#include "NetAddress.h"
#include "ut_sock.h"

namespace ff
{
	class NetPeer
	{
	public:
		NetPeer();
		NetPeer(std::string name);

		std::string mName;
		int32_t	   mIdx;
		ut_sock_t  mSock;
		NetAddress mAddress;
	};
}

#endif