/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_THREAD_H_
#define _UT_THREAD_H_

#include "ut_def.h"

__C_BEGIN_DECLS

typedef struct ut_thread		ut_thread_t;
typedef struct ut_mutex			ut_mutex_t;
typedef struct ut_spinlock		ut_spinlock_t;
typedef long long			thread_id_t;
typedef void* thread_handle;

/**
* 线程执行函数体.
*/
typedef int32_t(*ut_thread_func_t)(void*);

/**
* 创建一个线程执行体
*
* @param thread_func	线程执行函数体
* @param arg			传递给线程执行函数体的一个参数
* @return 				创建的线程操作指针，0表示创建失败
*/
ut_thread_t*	ut_thread_new(ut_thread_func_t thread_func, void* arg);

thread_handle	ut_thread_handle(ut_thread_t* thread);
/**
* 删除一个线程
*
* @param a_thread	线程操作指针
* @return 			NA
*/
void	ut_thread_delete(ut_thread_t* a_thread);

/**
* 删除一个线程
*
* @param a_thread	等待一个线程的结束
* @return 			NA
*/
void	ut_thread_join(ut_thread_t* a_thread);

/**
* 获取当前线程id
*
* @return 			线程id
*/
thread_id_t ut_thread_self(void);

/**
* 当前线程进入休眠状态
*
* @param milliseconds	休眠的毫秒数
* @return 				NA
*/
void	ut_sleep(int32_t milliseconds);

/**
* 当前线程让出执行权
*
* @return 				NA
*/
void	ut_yield();

/**
* 创建一个线程锁
*
* @return 				锁
*/
ut_mutex_t*		ut_mutex_new();

/**
* 删除一个线程锁
*
* @param a_mutex	锁
* @return 			NA
*/
void	ut_mutex_delete(ut_mutex_t*	a_mutex);

/**
* 锁住临界资源
*
* @param a_mutex	锁
* @return 			NA
*/
void	ut_mutex_lock(ut_mutex_t* a_mutex);

/**
* 释放临界资源
*
* @param a_mutex	锁
* @return 			NA
*/
void	ut_mutex_unlock(ut_mutex_t* a_mutex);

/**
* 试图锁住临界资源
*
* @param a_mutex	锁
* @return 			成功返回0，失败返回-1
*/
ut_err_code_t		ut_mutex_trylock(ut_mutex_t* a_mutex);

/**
* full memory barrier
*
* @return 			NA
*/
void	ut_sync_synchronize();

/**
* 比较并交换,如果ptr指向的值跟oval相等，就设置为nval的值，返回设置之前的值
*
* @return 			NA
*/
int16_t ut_cas(int16_t volatile* ptr, int16_t oval, int16_t nval);


/**
* 创建一个自旋锁
*
* @return 				锁
*/
ut_spinlock_t*		ut_spinlock_new();

/**
* 删除一个自旋锁
*
* @param a_lock	锁
* @return 			NA
*/
void	ut_spinlock_delete(ut_spinlock_t*	a_lock);

/**
* 锁住临界资源
*
* @param a_lock	锁
* @return 			NA
*/
void	ut_spinlock_lock(ut_spinlock_t* a_lock);

/**
* 释放临界资源
*
* @param a_lock	锁
* @return 			NA
*/
void	ut_spinlock_unlock(ut_spinlock_t* a_lock);

/**
* 试图锁住临界资源
*
* @param a_lock	锁
* @return 			成功返回0，失败返回-1
*/
ut_err_code_t		ut_spinlock_trylock(ut_spinlock_t* a_lock);

__C_END_DECLS

#endif
