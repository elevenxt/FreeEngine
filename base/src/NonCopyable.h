/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _US_NONCOPYABLE_
#define _US_NONCOPYABLE_

namespace ff
{
	struct NonCopyable
	{
	public:		
		NonCopyable() = default;
	private:
		NonCopyable & operator=(const NonCopyable&) = delete;
		NonCopyable(const NonCopyable&) = delete;
	};
}

#endif

