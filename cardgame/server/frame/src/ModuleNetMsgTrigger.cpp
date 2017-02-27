/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#include <functional>
#include <string>

#include "ModuleMgr.h"
#include "ModuleNetService.h"
#include "PlayerMgr.h"
#include "CfgIni.h"
#include "ModuleNetMsgTrigger.h"
#include "ModuleNetService.h"
#include "ModuleHotSwap.h"
#include "base.h"

using namespace ff;

bool ModuleNetMsgTrigger::initialize(ModuleMgr& mgr)
{
	
	mModuleDataSync = mgr.getModule<ModuleDataSync>();
	SYS_VERIFY_RV(mModuleDataSync != nullptr, false);

	ModuleNetService* pModNetService = mgr.getModule<ModuleNetService>();
	SYS_VERIFY_RV(pModNetService != nullptr, false);

	mNetService = pModNetService->getService("client");
	SYS_VERIFY_RV(mNetService != nullptr, false);

	if (!mNetService->init(this, 1024))
	{
		SYSLOG_ERROR("net service init failed.");
		return false;
	}

	if (!mNetService->createListener(CfgIni::instance().get<std::string>("server", "ip")
		, CfgIni::instance().get<int32_t>("server", "port")))
	{
		SYSLOG_ERROR("net service create listener failed.");
		return false;
	}
	
	HotSwapPlugin* hsPlugin = &HotSwapPluginProxy::instance();

	mMsgMgr.msgSetDefault(std::bind(&HotSwapPlugin::netMsg, hsPlugin
		, std::placeholders::_1, std::placeholders::_2
		, std::placeholders::_3, std::placeholders::_4));

	return true;
}

void ModuleNetMsgTrigger::finalize()
{
	
}

void ModuleNetMsgTrigger::newconn(NetService* netService, int32_t netid)
{
	SYSLOG_DEBUG(fmt::format("net connect {}", netid));
	
	Player* pPlayer = PlayerMgr::instance().createPlayer(netService, netid);
	SYS_VERIFY_R(pPlayer != nullptr);

}

void ModuleNetMsgTrigger::lostconn(NetService* netService, int32_t netid)
{
	SYSLOG_DEBUG(fmt::format("net lost {}", netid));
	PlayerImpl* pPlayer = PlayerMgr::instance().getByNetId(netid);
	mModuleDataSync->savePlayerData(*pPlayer);
	PlayerMgr::instance().deletePlayer(pPlayer);
}

void ModuleNetMsgTrigger::recvdata(NetService* netService, int32_t netid, const char* msg, int32_t len)
{
	Player* player = PlayerMgr::instance().getByNetId(netid);
	SYS_VERIFY_R(player != nullptr);
	// 消息最少2字节代表消息id
	SYS_CHECK_R(len >= (int32_t)sizeof(uint16_t));
	uint16_t msgid = *(uint16_t*)msg;

	int32_t rv = mMsgMgr.triggerMsg(*player, msgid, msg + sizeof(uint16_t), len-sizeof(uint16_t));
	if (rv < 0)
	{
		SYSLOG_DEBUG("trigger msg[{}] return error code {}", msgid, rv);
		//netService->close(netid);
	}
	mModuleDataSync->syncDirtyData();
}
