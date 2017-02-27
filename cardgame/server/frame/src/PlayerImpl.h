/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_PLAYER_IMPL_
#define _FF_PLAYER_IMPL_

#include "Player.h"
#include "NetService.h"
#include "GameDataImpl.h"

namespace ff
{
	class PlayerImpl : public Player
	{
	public:
		PlayerImpl(NetService* netService, int32_t netid);
		virtual void disconnect();
		virtual bool send(const char* data, int32_t len);
		virtual bool isLogined();
		virtual PlayerData& data();
		void setLogined(bool logined);
		PlayerDataImpl& dataImpl();
		int32_t getNetId();

	private:
		bool mLogined;
		NetService* mNetService;
		int32_t mNetId;
		int32_t mPlayerId;
		PlayerDataImpl mData;
	};
}

#endif