/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_net_handle.h"
#include "ut_net_util.h"
#include "ut_memory.h"


struct ut_channel_t*	ut_channel_malloc(struct ut_net_t* net)
{
	struct ut_channel_t* new_channel = 0;
	ut_list_t* freeele = ut_list_pop_head(&net->queue_free);
	if (freeele == 0)
	{
		return 0;
	}

	new_channel = (struct ut_channel_t*)freeele->value;
	ut_list_push_tail(&net->queue_inuse, freeele);
	return new_channel;
}

void ut_channel_free(struct ut_channel_t* channel)
{
	UT_CHECK_TRUE(channel != 0);
	struct ut_net_t*	net = channel->net;
	UT_VERIFY_TRUE(net != 0);

	ut_channel_finalize(channel);
	ut_list_remove(&channel->queue_inuse);
	ut_list_push_tail(&net->queue_free, &channel->queue_inuse);

FAIL:
	return;
}


struct ut_channel_t* ut_channel_create(
	int32_t idx, struct ut_net_t* net)
{
	struct ut_channel_t* channel = 0;
	// 参数有效性检查
	UT_VERIFY_TRUE(idx >= 0);
	UT_VERIFY_TRUE(net != 0);
	UT_VERIFY_TRUE(net->cfg.st_channel_size >= sizeof(struct ut_channel_t));

	channel = (struct ut_channel_t*)ut_new(net->cfg.st_channel_size);
	UT_VERIFY_TRUE(channel != 0);
	channel->sock = ut_sock_invalid();
	ut_list_init(&channel->queue_inuse, channel);
	channel->index = idx;
	channel->net = net;

	return channel;

FAIL:
	if (channel != 0)
	{
		ut_channel_delete(channel);
	}
	return 0;
}

void	ut_channel_delete(struct ut_channel_t* channel)
{
	UT_VERIFY_TRUE(channel != 0);
	ut_channel_finalize(channel);

	UT_DELETE(channel);

FAIL:
	return;
}

void ut_channel_finalize(struct ut_channel_t* channel)
{
	UT_VERIFY_TRUE(channel != 0);
	channel->connection_data = 0;
	channel->user_data = 0;
	if (ut_sock_isvalidate(channel->sock))
	{
		ut_sock_close(channel->sock);
		channel->sock = ut_sock_invalid();
	}

FAIL:
	return;
}

