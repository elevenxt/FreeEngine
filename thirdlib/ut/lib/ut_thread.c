/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/




#include "ut_thread.h"
#include "ut_defines.h"
#include "ut_memory.h"

#ifdef UT_PLATFORM_WINDOWS
#include <Windows.h>
#include <process.h>
#endif

#ifdef UT_PLATFORM_LINUX
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#endif


struct ut_spinlock
{
	volatile int16_t	lock;
};

#ifdef UT_PLATFORM_WINDOWS

struct ut_thread
{
	ut_thread_func_t	thread_func;
	void*				arg;
	HANDLE				handle;
};

struct ut_mutex
{
	CRITICAL_SECTION mutex;
};

static int32_t __stdcall inner_thread_func_t(void* arg)
{
	ut_thread_t*	a_thread = (ut_thread_t*)arg;
	int32_t unret = (*a_thread->thread_func)(a_thread->arg);
	_endthreadex(0);

	return unret;
}

ut_thread_t*	ut_thread_new(ut_thread_func_t thread_func, void* arg)
{
	ut_thread_t*	a_thread = UT_NEW(ut_thread_t);
	if (0 == a_thread)
	{
		return 0;
	}	

	a_thread->thread_func = thread_func;
	a_thread->arg = arg;

	a_thread->handle = (HANDLE)_beginthreadex(0, 0, inner_thread_func_t, a_thread, 0, 0);

	if (0 == a_thread->handle)
	{
		ut_thread_delete(a_thread);
		a_thread = 0;
	}

	return a_thread;
}

thread_handle	ut_thread_handle(ut_thread_t* thread)
{
	return thread->handle;
}

void	ut_thread_delete(ut_thread_t* a_thread)
{
	TerminateThread(a_thread->handle, -1);
	free(a_thread);
}

void	ut_thread_join(ut_thread_t* a_thread)
{
	WaitForSingleObject(a_thread->handle, INFINITE);
}

thread_id_t ut_thread_self(void)
{
	return GetCurrentThreadId();
}

void	ut_sleep(int32_t milliseconds)
{
	Sleep(milliseconds);
}

void	ut_yield()
{
	Sleep(0);
}

ut_mutex_t*		ut_mutex_new()
{
	ut_mutex_t*	a_mutex = UT_NEW(ut_mutex_t);
	if (0 == a_mutex)
	{
		return 0;
	}	

	InitializeCriticalSection(&a_mutex->mutex);

	return a_mutex;
}

void	ut_mutex_delete(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_R(0 != a_mutex);

	DeleteCriticalSection(&a_mutex->mutex);

	UT_DELETE(a_mutex);
}

void	ut_mutex_lock(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_R(0 != a_mutex);

	EnterCriticalSection(&a_mutex->mutex);
}

void	ut_mutex_unlock(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_R(0 != a_mutex);

	LeaveCriticalSection(&a_mutex->mutex);
}

ut_err_code_t		ut_mutex_trylock(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_RV(0 != a_mutex, ut_error);

	return TryEnterCriticalSection(&a_mutex->mutex)?ut_success:ut_error;
}

void	ut_sync_synchronize()
{
	MemoryBarrier();
}

int16_t ut_cas(int16_t volatile* ptr, int16_t oval, int16_t nval)
{
	return InterlockedCompareExchange16(ptr, nval, oval);
}

#endif

#ifdef UT_PLATFORM_LINUX

struct ut_thread
{
	ut_thread_func_t	thread_func;
	void*				arg;
	pthread_t			handle;
};

struct ut_mutex
{
	pthread_mutex_t mutex;
};

union ut_i2p
{
	int32_t iv;
	void* pv;
};

static void* inner_thread_func_t(void* arg)
{
	union ut_i2p v;
	ut_thread_t*	a_thread = (ut_thread_t*)arg;
	
	v.pv = 0;
	v.iv = (*a_thread->thread_func)(a_thread->arg);
	return v.pv;
}

ut_thread_t*	ut_thread_new(ut_thread_func_t thread_func, void* arg)
{
	ut_thread_t*	a_thread = UT_NEW(ut_thread_t);
	if (0 == a_thread)
	{
		return 0;
	}	

	a_thread->thread_func = thread_func;
	a_thread->arg = arg;

	if(pthread_create(&a_thread->handle, NULL, inner_thread_func_t, a_thread) != 0)
	{
		ut_thread_delete(a_thread);
		a_thread = 0;
	}

	return a_thread;
}

void	ut_thread_delete(ut_thread_t* a_thread)
{
	pthread_cancel(a_thread->handle);
	free(a_thread);
}

void	ut_thread_join(ut_thread_t* a_thread)
{
	pthread_join(a_thread->handle, 0);
}

thread_id_t ut_thread_self(void)
{
	return (thread_id_t) pthread_self();
}

void	ut_sleep(int32_t milliseconds)
{
	usleep(milliseconds*1000);
}

void	ut_yield()
{
	sched_yield();
}

ut_mutex_t*		ut_mutex_new()
{
	ut_mutex_t*	a_mutex = UT_NEW(ut_mutex_t);
	if (0 == a_mutex)
	{
		return 0;
	}	

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&a_mutex->mutex, &attr);

	return a_mutex;
}

void	ut_mutex_delete(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_R(0 != a_mutex);

	pthread_mutex_destroy(&a_mutex->mutex);
	free(a_mutex);
}

void	ut_mutex_lock(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_R(0 != a_mutex);

	pthread_mutex_lock(&a_mutex->mutex);
}

void	ut_mutex_unlock(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_R(0 != a_mutex);

	pthread_mutex_unlock(&a_mutex->mutex);
}

ut_err_code_t		ut_mutex_trylock(ut_mutex_t*	a_mutex)
{
	UT_ASSERT_RV(0 != a_mutex, ut_error);

	return pthread_mutex_trylock(&a_mutex->mutex)==0?ut_success:ut_error;
}

void	ut_sync_synchronize()
{
	__sync_synchronize();
}

int16_t ut_cas(int16_t volatile* ptr, int16_t oval, int16_t nval)
{
	return __sync_val_compare_and_swap(ptr, oval, nval);
}

#endif

ut_spinlock_t*		ut_spinlock_new()
{
	ut_spinlock_t*	a_lock = UT_NEW(ut_spinlock_t);
	if (0 == a_lock)
	{
		return 0;
	}	

	a_lock->lock = 0;

	return a_lock;
}

void	ut_spinlock_delete(ut_spinlock_t*	a_lock)
{
	UT_DELETE(a_lock);
}

void	ut_spinlock_lock(ut_spinlock_t* a_lock)
{
	while (ut_cas(&a_lock->lock, 0, 1) == 1);
}

void	ut_spinlock_unlock(ut_spinlock_t* a_lock)
{
	a_lock->lock = 0;
}

ut_err_code_t		ut_spinlock_trylock(ut_spinlock_t* a_lock)
{
	if (ut_cas(&a_lock->lock, 0, 1) == 1)
	{
		return ut_success;
	}

	return ut_error;
}