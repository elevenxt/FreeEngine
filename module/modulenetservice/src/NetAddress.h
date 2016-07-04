/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_NET_ADDRESS_
#define _US_NET_ADDRESS_

#include <string>
#include <cinttypes>


namespace ff
{
	class NetAddress
	{
	public:
		NetAddress();
		NetAddress(std::string ip, int32_t port);

	public:
		std::string ip();
		int32_t port();

		void setIp(const std::string& ip);
		void setPort(int32_t port);

	private:
		std::string mip;
		int32_t mport;
	};
}
#endif