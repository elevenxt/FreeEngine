/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_PLAYER_
#define _FF_PLAYER_

#include <cinttypes>
#include "GameData.h"
#include "scmsg.h"

namespace ff
{
	class Player
	{
	public:
		virtual ~Player() {};
		virtual void disconnect() = 0;
		virtual bool send(const char* data, int32_t ln) = 0;
		virtual bool isLogined() = 0;
		virtual PlayerData& data() = 0;

		template<typename MSG>
		bool send(MSG& msg)
		{
			static char sTmpBuf[4096];
			uint16_t tsize = sizeof(uint16_t) + msg.ByteSize();
			if (tsize > 4096)
			{
				return false;
			}

			*(uint16_t*)sTmpBuf = msg_st2id<scmsg_group, MSG>::ID;
			if (!msg.SerializeToArray(sTmpBuf+sizeof(uint16_t), 4096-sizeof(uint16_t)))
			{
				return false;
			}

			return send(sTmpBuf, tsize);
		}
	};
}

#endif