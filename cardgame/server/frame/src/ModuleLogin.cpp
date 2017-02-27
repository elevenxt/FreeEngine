/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/

#include <string>
#include <functional>

#include "CfgIni.h"
#include "ModuleLogin.h"
#include "ModuleNetService.h"
#include "ModuleNetMsgTrigger.h"
#include "ModuleMgr.h"
#include "base.h"
#include "PlayerMgr.h"
#include "PlayerImpl.h"
#include "ConstString.h"


using namespace ff;

bool ModuleLogin::initialize(ModuleMgr& mgr)
{
	ModuleNetMsgTrigger* pNetMsgTrigger = mgr.getModule<ModuleNetMsgTrigger>();
	SYS_VERIFY_RV(REG_NETMSG(pNetMsgTrigger, ModuleLogin, netMsg, cs_login), false);
	
	mModuleRocksDb = mgr.getModule<ModuleRocksDb>();
	SYS_VERIFY_RV(mModuleRocksDb != nullptr, false);

	mModuleDataSync = mgr.getModule<ModuleDataSync>();
	SYS_VERIFY_RV(mModuleDataSync != nullptr, false);
	
	return true;
}

void ModuleLogin::finalize()
{
	
}

int32_t ModuleLogin::netMsg(Player& player, const cs_login& msg)
{
	PlayerImpl& pi = dynamic_cast<PlayerImpl&>(player);
	SYSLOG_DEBUG("player [{}] logined.", msg.id());

	std::string val = mModuleRocksDb->load(fmt::format("{}_{}", CS::DBTAB_PLAYER, msg.id()));
	if (val.empty())
	{
		// 创建新用户
		BaseInfo& bi = pi.data().getBaseInfo();
		bi.setId(msg.id().c_str());
		bi.setName(msg.id().c_str());
		bi.setDiamond(1000);
		bi.setGold(10000);
		bi.setLevel(1);

		TeamInfo& ti = pi.data().getTeamInfo();
		Card& c0 = ti.getTeamMember(0);
		c0.setId(1);
		c0.setLevel(1);

		pi.setLogined(true);
	}
	else
	{
		// 老用户登陆
		pi.setLogined(true);

		PlayerDataProto pdProto;
		if (!pdProto.ParseFromString(val)) {
			SYSLOG_WARNING("proto parse failed[{}].", msg.id());
		}

		pi.dataImpl().fromProto(pdProto);
	}

	pi.data().getSysInfo().setServerName(CfgIni::instance().get<std::string>("server", "name").c_str());
	pi.data().getSysInfo().setServerTime(time(0));

	sc_login_res loginRes;
	loginRes.set_res(1);

	PlayerMgr::instance().bindUserId(player);
	
	if (!player.send(loginRes))
	{
		SYSLOG_WARNING("send msg sc_login_res failed.");
		return -1;
	}

	if (!mModuleDataSync->syncData(player))
	{
		return -1;
	}

	return 0;
}

