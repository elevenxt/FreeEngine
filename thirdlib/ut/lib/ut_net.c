/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_net.h"
#include "ut_net_handle.h"
#include "ut_net_util.h"
#include "ut_memory.h"

static struct ut_net_config_t def_cfg = 
{
	sizeof(struct ut_net_t),
	sizeof(struct ut_channel_t),
	1024,
};

struct ut_net_config_t*	ut_net_config_create()
{
	struct ut_net_config_t* cfg = UT_NEW(struct ut_net_config_t);
	UT_VERIFY_TRUE(cfg != 0);

	*cfg = def_cfg;
	return cfg;

FAIL:
	if (cfg != 0)
	{
		UT_DELETE(cfg);
	}

	return 0;
}

void	ut_net_config_delete(struct ut_net_config_t* cfg)
{
	UT_VERIFY_TRUE(cfg != 0);
	UT_DELETE(cfg);
FAIL:
	return;
}

int32_t		ut_net_config_set_connectionlimit(struct ut_net_config_t* cfg, int32_t limit)
{
	UT_VERIFY_TRUE(cfg != 0);
	UT_VERIFY_TRUE(limit > 0 && limit <= 65536);

	cfg->num_connection_limit = limit;
	return 0;

FAIL:
	return -1;
}

struct ut_net_t*	ut_net_create(struct ut_net_config_t* cfg,
	new_connection newfunc, lost_connection lostfunc, void* data)
{
	struct ut_net_t* net = 0;
	int32_t i = 0;

	if (cfg == 0)
	{
		cfg = &def_cfg;
	}

	UT_VERIFY_TRUE(cfg->st_net_size >= sizeof(struct ut_net_t));
	UT_VERIFY_TRUE(cfg->st_channel_size >= sizeof(struct ut_channel_t));
	UT_VERIFY_TRUE(cfg->num_connection_limit > 0);
	UT_VERIFY_TRUE(newfunc != 0);
	UT_VERIFY_TRUE(lostfunc != 0);

	net = (struct ut_net_t*)ut_new(cfg->st_net_size);
	UT_VERIFY_TRUE(net != 0);

	net->cfg = *cfg;
	ut_list_init(&net->queue_free, net);
	ut_list_init(&net->queue_inuse, net);

	net->new_func = newfunc;
	net->lost_func = lostfunc;
	net->user_data = data;

	for (i = 0; i < cfg->num_connection_limit; i++)
	{
		struct ut_channel_t* channel = ut_channel_create(i, net);
		UT_VERIFY_TRUE(channel != 0);
		ut_list_push_tail(&net->queue_free, &channel->queue_inuse);
	}

	UT_VERIFY_TRUE(0 == init_net_handle(net));

	return net;

FAIL:
	ut_net_delete(net);
	return 0;
}

void	ut_net_delete(struct ut_net_t* net)
{
	ut_list_t* lst = 0;
	UT_VERIFY_TRUE(0 != net);
	// 停止工作
	while (0 != (lst = ut_list_pop_head(&net->queue_inuse)))
	{
		struct ut_channel_t* channel = (struct ut_channel_t*)(lst->value);
		ut_channel_delete(channel);
	}
	while (0 != (lst = ut_list_pop_head(&net->queue_free)))
	{
		struct ut_channel_t* channel = (struct ut_channel_t*)(lst->value);
		ut_channel_delete(channel);
	}

	uninit_net_handle(net);
	// 释放资源
	UT_DELETE(net);

FAIL:
	return;
}

int32_t		ut_net_send(struct ut_channel_t* channel, const char* data, int32_t datalen)
{
	UT_VERIFY_TRUE(channel != 0);
	UT_VERIFY_TRUE(data != 0);
	UT_VERIFY_TRUE(datalen > 0);

	return ut_sock_send(channel->sock, data, datalen);

FAIL:
	return 0;
}


void	ut_net_channel_close(struct ut_channel_t* channel)
{
	UT_VERIFY_TRUE(channel != 0);
	ut_sock_shutdown(channel->sock);

FAIL:
	return;
}

struct ut_channel_t*	ut_net_deliver_socket(struct ut_net_t* net,
	ut_sock_t sock, recv_data rcvfunc, void* data)
{
	struct ut_channel_t* channel = 0;

	UT_VERIFY_TRUE(net != 0);
	UT_VERIFY_TRUE(rcvfunc != 0);
	
	UT_CHECK_TRUE(0 == ut_sock_set_keepalive(sock));
	UT_CHECK_TRUE(0 == ut_sock_set_nonblock(sock));

	// 申请通道资源
	channel = ut_channel_malloc(net);
	UT_CHECK_TRUE(channel != 0);

	UT_CHECK_TRUE(0 == ut_sock_getsock_info(sock, &channel->info.local_ip, &channel->info.local_port));
	UT_CHECK_TRUE(0 == ut_sock_getpeer_info(sock, &channel->info.remote_ip, &channel->info.remote_port));

	channel->sock = sock;
	channel->connection_data = rcvfunc;
	channel->user_data = data;

	UT_CHECK_TRUE(0 == do_deliver_socket(net, channel));
	net->new_func(channel, net->user_data, channel->user_data);

	return channel;

FAIL:
	ut_sock_close(sock);
	if (channel != 0)
	{
		channel->sock = ut_sock_invalid();
		channel->connection_data = 0;
		channel->user_data = 0;
		ut_channel_free(channel);
	}

	return 0;
}


int32_t		ut_net_channel_index(struct ut_channel_t* channel)
{
	UT_VERIFY_TRUE(channel != 0);
	return channel->index;

FAIL:
	return -1;
}

int32_t		ut_net_channel_getname(struct ut_channel_t* channel, int32_t* ip, int32_t* port)
{
	UT_VERIFY_TRUE(channel != 0 && ip != 0 && port != 0);

	*ip = channel->info.local_ip;
	*port = channel->info.local_port;
	
	return 0;
	
FAIL:
	return -1;
}

int32_t		ut_net_channel_getpeer(struct ut_channel_t* channel, int32_t* ip, int32_t* port)
{
	UT_VERIFY_TRUE(channel != 0 && ip != 0 && port != 0);

	*ip = channel->info.remote_ip;
	*port = channel->info.remote_port;

	return 0;

FAIL:
	return -1;
}
