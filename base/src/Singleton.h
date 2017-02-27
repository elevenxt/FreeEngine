/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _FF_SINGLETON_
#define _FF_SINGLETON_

#include <assert.h>

namespace ff
{
	// 单件基类
	template<typename T>
	class Singleton
	{
	private:
		Singleton(const Singleton&) = delete;
		void operator=(const Singleton&) = delete;

	protected:
		Singleton()
		{
			static Singleton*	mInstance = nullptr;
			assert(mInstance == nullptr);
			mInstance = this;
		};
		virtual ~Singleton(){};

	public:
		//  所有单件必须在主线程中实例化
		static T& instance()
		{
			static T t;
			return t;
		}

	private:		
	};
}
#endif