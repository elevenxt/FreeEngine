/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <iostream>

#include "ModuleClient.h"
#include "base.h"
#include "ModuleMgr.h"
#include "ModuleNetService.h"
#include "SpinlockGuard.h"

using namespace ff::demo;
using namespace ff;

bool ModuleClient::initialize(ModuleMgr& mgr)
{
	ff::ModuleNetService* pNetService = mgr.getModule<ff::ModuleNetService>();
	SYS_VERIFY_RV(pNetService != nullptr, false);
	mNet = pNetService->getService("chatclient");
	SYS_VERIFY_RV(mNet->init(this, 1024), false);

	SYS_VERIFY_RV(mNet->connect("127.0.0.1", 101011), false);

	return true;
}

void ModuleClient::finalize()
{
	
}

int32_t ModuleClient::runOnce()
{
	/*说话，也就是从键盘获取数据，发送到服务器*/
	char buf[1024] = { 0 };
	std::cin.clear();
	std::cin.sync();
	std::cin.getline(buf, 1024);
	std::string msg(buf);
	SpinlockGuard lg(mLock);
	mNet->send(mId, msg.c_str(), msg.size());
	return 10;
}

void ModuleClient::newconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("new connection {}.", id);
	mId = id;
}

void ModuleClient::lostconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("lost connection {}.", id);
	mId = -1;
}

void ModuleClient::recvdata(ff::NetService* net, int32_t id, const char* data, int32_t datalen)
{
	SpinlockGuard lg(mLock);
	/*打印玩家说的话*/
	std::cout << std::string(data, datalen) << std::endl;
}

