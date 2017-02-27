/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_PROTOBUFMSG_MGR_
#define _US_PROTOBUFMSG_MGR_

#include <vector>
#include <functional>
#include <cinttypes>

namespace ff
{
	// 消息路由表
	template<typename KEY, typename CHANNEL>
	class ProtobufMsgMgr
	{
	private:
		class MsgSlotBase
		{
		public:
			virtual int triggerMsg(CHANNEL& channel, const char* data, int32_t len) = 0;
		};

		template<typename PROTO>
		class MsgSlot : public MsgSlotBase
		{
		public:
			MsgSlot(std::function<int32_t(CHANNEL&, const PROTO&)> msgfunc)
			{
				mFunc = msgfunc;
			}

			virtual int triggerMsg(CHANNEL& channel, const char* data, int32_t len)
			{
				PROTO proto;
				if (!proto.ParseFromArray(data, len))
				{
					return -1;
				}

				return mFunc(channel, proto);
			}

		private:
			std::function<int32_t(CHANNEL&, const PROTO&)> mFunc;
		};

	public:
		ProtobufMsgMgr()
		{
			mDefaultMsg = nullptr;
		}

		~ProtobufMsgMgr()
		{
			for (std::map<KEY, MsgSlotBase*>::iterator iter = mMsgMap.begin();
				iter != mMsgMap.end(); ++iter)
			{
				delete (iter->second);
			}
		}

		bool init(std::function<int32_t(CHANNEL&, const KEY&, const char*, int32_t)> defaultMsg)
		{
			mDefaultMsg = defaultMsg;
			return mDefaultMsg;
		}

		template<typename PROTO>
		bool msgConnect(const KEY& key, std::function<int32_t(CHANNEL&, const PROTO&)> msgfunc)
		{
			if (mMsgMap.find(key) != mMsgMap.end())
			{
				return false;
			}

			mMsgMap[key] = new MsgSlot<PROTO>(msgfunc);
			return true;
		}		

		int32_t triggerMsg(CHANNEL& channel, const KEY& key, const char* data, int32_t len)
		{
			std::map<KEY, MsgSlotBase*>::iterator iter = mMsgMap.find(key);
			if (iter == mMsgMap.end())
			{
				if (mDefaultMsg)
				{
					return mDefaultMsg(channel, key, data, len);
				}
				return -2;
			}

			MsgSlotBase* trigger = iter->second;

			return trigger->triggerMsg(channel, data, len);
		}

	private:
		std::map<KEY, MsgSlotBase*>	mMsgMap;
		std::function<int32_t(CHANNEL&, const KEY&, const char*, int32_t)>	mDefaultMsg;
	};

}

#endif
