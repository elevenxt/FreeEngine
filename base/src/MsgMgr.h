/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_MSG_MGR_
#define _FF_MSG_MGR_

#include <cinttypes>
#include <vector>
#include <functional>

#include "base.h"

template<typename GROUP, typename ST>
struct msg_st2id;
template<typename GROUP, int ID>
struct msg_id2st;

namespace ff
{
	template<typename T>
	class MsgTrigger
	{
	public:
		virtual ~MsgTrigger() {};
		virtual	int triggerMsg(T& t, const char* data, int len) = 0;
	};

	template<typename T, typename PROTO>
	class ProtoTrigger : public MsgTrigger<T>
	{
	public:
		ProtoTrigger(std::function<int32_t(T& t, const PROTO& proto)> func)
		{
			mMsgFunc = func;
		}

		virtual int triggerMsg(T& t, const char* data, int32_t len)
		{
			PROTO proto;
			if (!proto.ParseFromArray(data, len))
			{
				return -1;
			}

			return mMsgFunc(t, proto);
		}

	private:
		std::function<int(T& t, const PROTO& proto)> mMsgFunc;
	};

	template<typename T, typename GROUP>
	class MsgMgr
	{
	public:
		MsgMgr()
		{
			mDefaultMsg = nullptr;
		}
		~MsgMgr()
		{
			for (auto iter = mMsgMap.begin();
				iter != mMsgMap.end(); ++iter)
			{
				for (auto it = (*iter).begin();
					it != (*iter).end(); ++it)
				{
					delete (*it);
				}
			}
		}

		template<typename PROTO>
		bool msgConnect(std::function<int32_t(T& t, const PROTO& proto)> msgfunc)
		{
			ProtoTrigger<T, PROTO>*	protoTrigger = new ProtoTrigger<T, PROTO>(msgfunc);
			int id = msg_st2id<GROUP,PROTO>::ID;
			if (id >= (int32_t)mMsgMap.size())
			{
				mMsgMap.resize(id+1);
			}
			mMsgMap[id].push_back(protoTrigger);

			return true;
		}

		bool msgSetDefault(std::function<int32_t(T&, int32_t, const char*, int32_t)> defaultMsg)
		{
			mDefaultMsg = defaultMsg;
			return true;
		}

		int triggerMsg(T& channel, int32_t msgid, const char* data, int32_t len)
		{
			if (msgid<0 || msgid>=(int32_t)mMsgMap.size() || mMsgMap[msgid].empty())
			{
				if (mDefaultMsg)
				{
					return mDefaultMsg(channel, msgid, data, len);
				}
				return -1;
			}
			for (auto iter = mMsgMap[msgid].begin();
				iter != mMsgMap[msgid].end(); ++iter)
			{
				int32_t rv = (*iter)->triggerMsg(channel, data, len);
				if (rv < 0)
				{
					return rv;
				}
			}
			return 0;
		}

	private:
		std::vector<std::vector<MsgTrigger<T>*>>	mMsgMap;
		std::function<int32_t(T&, int32_t, const char*, int32_t)> mDefaultMsg;
	};

}

#endif
