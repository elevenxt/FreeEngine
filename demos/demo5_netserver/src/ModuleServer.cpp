/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleServer.h"
#include "base.h"
#include "ModuleMgr.h"
#include "ModuleNetService.h"

using namespace ff::demo;


bool ModuleServer::initialize()
{
	/*获取网络服务器模块*/
	ff::ModuleNetService* pNetService = ff::ModuleMgr::instance().getModule<ff::ModuleNetService>();
	SYS_VERIFY_RV(pNetService != nullptr, false);
	/*创建一个网络服务*/
	mNet = pNetService->getService("testserver");
	SYS_VERIFY_RV(mNet->init(this, 1024), false);
	/*建立监听器*/
	SYS_VERIFY_RV(mNet->createListener("127.0.0.1", 101011), false);

	return true;
}

void ModuleServer::finalize()
{

}

void ModuleServer::newconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("new connection {}.", id);
	mIds.push_back(id);
}

void ModuleServer::lostconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("lost connection {}.", id);
	std::remove(mIds.begin(), mIds.end(), id);
}

void ModuleServer::recvdata(ff::NetService* net, int32_t id, const char* data, int32_t datalen)
{
	/*打印收到的数据*/
	SYSLOG_DEBUG("recv data [{}]:[{}]", id, std::string(data, datalen));
}
