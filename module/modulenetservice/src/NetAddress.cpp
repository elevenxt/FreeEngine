/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "NetAddress.h"

using namespace ff;


NetAddress::NetAddress()
{

}

NetAddress::NetAddress(std::string ip, int32_t port)
{
	mip = ip;
	mport = port;
}

std::string NetAddress::ip()
{
	return mip;
}

int32_t NetAddress::port()
{
	return mport;
}

void NetAddress::setIp(const std::string& ip)
{
	mip = ip;
}

void NetAddress::setPort(int32_t port)
{
	mport = port;
}
