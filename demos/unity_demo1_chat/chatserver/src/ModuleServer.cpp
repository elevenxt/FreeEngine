/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleServer.h"
#include "base.h"
#include "ModuleMgr.h"
#include "ModuleNetService.h"
#include "msg.pb.h"
#include "strnormalize.h"

using namespace ff::demo;
using namespace FreeEngineMsg;


bool ModuleServer::initialize()
{
	ff::ModuleNetService* pNetService = ff::ModuleMgr::instance().getModule<ff::ModuleNetService>();
	SYS_VERIFY_RV(pNetService != nullptr, false);
	mNet = pNetService->getService("chatserver");
	SYS_VERIFY_RV(mNet->init(this, 1024), false);
	SYS_VERIFY_RV(mNet->createListener("127.0.0.1", 10101), false);

	return true;
}

void ModuleServer::finalize()
{

}

void ModuleServer::newconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("new connection {}.", id);
	mIds.push_back(id);

	FEMsg msg;
	msg.set_msgtype(FEMsg_MSG_Type_Info);
	msg.mutable_gameinfo()->mutable_version()->append("1.0.0");
	int length = msg.ByteSize();
	char* buf = new char[length];
	msg.SerializeToArray(buf, length);
	mNet->send(id, buf, length);
}

void ModuleServer::lostconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("lost connection {}.", id);
	std::remove(mIds.begin(), mIds.end(), id);
}

void ModuleServer::recvdata(ff::NetService* net, int32_t id, const char* data, int32_t datalen)
{
	FEMsg msg;
	msg.ParseFromArray(data, datalen);
	//msg.PrintDebugString();

	switch (msg.msgtype())
	{
		case FEMsg_MSG_Type_Info:		
		break;
		case FEMsg_MSG_Type_Talk:
		{
			//c#的protobuf在c++这解析中文打印会乱码，需要把字符串从utf8转为GBK
			//转码参考http://blog.csdn.net/ghevinn/article/details/9838175
			str_normalize_init();
			uint32_t utf8_len = strlen(msg.talk().content().c_str());
			uint32_t gbk_len = strlen(msg.talk().content().c_str());
			uint32_t utf8buffer_len = utf8_len * 3 + 1;
			uint32_t gbkbuffer_len = gbk_len * 2 + 1;
			char *gbkbuffer = (char *)malloc(gbkbuffer_len);
			utf8_to_gbk(msg.talk().content().c_str(), utf8_len, &gbkbuffer, &gbkbuffer_len);

			SYSLOG_DEBUG("{} say: {}   ", msg.talk().sender(), gbkbuffer);
			for (std::vector<int32_t>::iterator iter = mIds.begin();
				iter != mIds.end(); ++iter)
			{
				mNet->send(*iter, data, datalen);
			}
			break; 
		}

		default:
		break;
	}
}

