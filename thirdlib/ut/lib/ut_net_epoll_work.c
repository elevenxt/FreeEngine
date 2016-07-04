/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_def.h"

#ifdef UT_PLATFORM_LINUX
#include "ut_net_define.h"
#include "ut_net.h"
#include "ut_math.h"
#include "ut_net_util.h"
#include "ut_net_handle.h"
#include "ut_memory.h"
#include "ut_math.h"
#include <sys/resource.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>


int32_t init_net_handle(struct ut_net_t* net)
{
	net->epoll_handle = epoll_create(65536);
	return net->epoll_handle > 0 ? 0 : -ut_lasterror();
}

void uninit_net_handle(struct ut_net_t* net)
{
	UT_CHECK_TRUE (net != 0);

	close(net->epoll_handle);
	net->epoll_handle = -1;

FAIL:
	return;
}

int32_t do_deliver_socket(struct ut_net_t* net, struct ut_channel_t* channel)
{
	int32_t err = 0;

	struct epoll_event eevent;
	eevent.data.ptr = channel;
	eevent.events = EPOLLIN;

	err = epoll_ctl(net->epoll_handle, EPOLL_CTL_ADD, channel->sock, &eevent);

	return err == 0?0:-ut_lasterror();
}

static void do_lost_connection(struct ut_channel_t* channel)
{
	UT_VERIFY_TRUE(0 != channel);
	UT_VERIFY_TRUE(0 != channel->net);

	channel->net->lost_func(channel, channel->net->user_data, channel->user_data);
	ut_sock_close(channel->sock);
	channel->sock = ut_sock_invalid();
	ut_channel_free(channel);
	epoll_ctl(channel->net->epoll_handle, EPOLL_CTL_DEL, channel->sock, 0);

FAIL:
	return;
}

int32_t ut_net_pool_once(struct ut_net_t* net, int32_t weight, int32_t waittime)
{
	int32_t i = 0;
	int32_t wait_num = 0;

	weight = ut_clip(weight, 32, MAX_WAIT_EVENT);
	wait_num = epoll_wait(net->epoll_handle, net->wait_event
		, weight, waittime);

	for ( ; i < wait_num; i++)
	{
		struct ut_channel_t* channel = (struct ut_channel_t*)net->wait_event[i].data.ptr;
		
		if ((net->wait_event[i].events & ~EPOLLIN) == 0)
		{
			// 处理接收事件
			int32_t nrcvl = ut_sock_recv(channel->sock, net->rcv_buf, 
				EPOLL_RCV_BUF_SIZE);
			if (nrcvl > 0)
			{
				channel->connection_data(channel, net->rcv_buf, 
					nrcvl, net->user_data, channel->user_data);
			}
			else if (nrcvl == 0 || (nrcvl != EINTR && nrcvl != EAGAIN))
			{
				do_lost_connection(channel);
			}
		}
		else
		{
			// 处理错误
			do_lost_connection(channel);
		}
	}

	return wait_num>=0?wait_num:-ut_lasterror();
}

#endif
