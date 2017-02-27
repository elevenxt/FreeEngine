/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include "NetPeer.h"


using namespace ff;


NetPeer::NetPeer()
{
	mSock = ut_sock_invalid();
	mIdx = -1;
}

NetPeer::NetPeer(std::string name)
{
	mSock = ut_sock_invalid();
	mIdx = -1;
	mName = name;
}