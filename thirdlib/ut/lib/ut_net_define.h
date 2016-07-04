/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _NET_DEFINE_
#define _NET_DEFINE_

#include "ut_net.h"
#include "ut_sock.h"
#include "ut_list.h"

#ifdef UT_PLATFORM_WINDOWS
#include <Winsock2.h>
#endif
#ifdef UT_PLATFORM_LINUX
#include <sys/epoll.h>
#endif

__C_BEGIN_DECLS

// 网络设置数据
struct ut_net_config_t
{
	int32_t		st_net_size;
	int32_t		st_channel_size;
	int32_t		num_connection_limit;
};

// 网络连接信息
struct ut_channel_info_t
{
	// 本地绑定ip
	int32_t		local_ip;
	// 对端ip
	int32_t		remote_ip;
	// 本地绑定端口
	int32_t		local_port;
	// 对端端口
	int32_t		remote_port;
	int64_t		bytes_recved;		// 接收数据总量
	int64_t		bytes_sended;		// 发送数据总量
};

#ifdef UT_PLATFORM_WINDOWS
enum IOType 
{
	IO_RECEIVE,		// 数据接收事件
};

typedef struct _IOOverlapped
{
	OVERLAPPED		overlapped;
	enum IOType		io_type;
	WSABUF			wsabuf;
}IOOverlapped;

#define OVERLAPPED_BUF_SIZE		4096
#endif

#ifdef UT_PLATFORM_LINUX
#define MAX_WAIT_EVENT		1024
#define EPOLL_RCV_BUF_SIZE	1024*128
#endif

struct ut_net_t;
struct ut_channel_t
{
	int32_t				index;
	struct ut_net_t*	net;

	ut_list_t			queue_inuse;	// 这个队列中的通道正在使用中,和queue_free复用一个

	ut_sock_t			sock;			// 网络套接字
	struct ut_channel_info_t info;
#ifdef UT_PLATFORM_WINDOWS
	char			rcv_buf[OVERLAPPED_BUF_SIZE];		// 接收缓冲区
	IOOverlapped	io_overlapped;		// win32系统用重叠数据
#endif
	void(*connection_data)(struct ut_channel_t* channel, const char* data
		, int32_t datalen, void* netdata, void* channeldata);
	void*	user_data;
};

// 网络句柄数据
struct ut_net_t
{
	// 用户配置数据
	struct ut_net_config_t			cfg;
#ifdef UT_PLATFORM_LINUX
	// linux 专用
	int32_t				epoll_handle;		// epoll 句柄
	struct epoll_event	wait_event[MAX_WAIT_EVENT];			// epoll事件缓存
	char	rcv_buf[EPOLL_RCV_BUF_SIZE];
#endif
#ifdef UT_PLATFORM_WINDOWS
	// windos专用
	// 完成端口句柄
	HANDLE				io_complete_port;	// IOCP端口
#endif
	ut_list_t		queue_inuse;		// 正在使用的队列
	ut_list_t		queue_free;			// 空闲队列
	void(*new_func)(struct ut_channel_t* channel, void* netdata, void* channeldata);
	void(*lost_func)(struct ut_channel_t* channel, void* netdata, void* channeldata);
	void*	user_data;
};


__C_END_DECLS

#endif