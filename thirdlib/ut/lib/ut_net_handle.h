/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _NET_HANDLE_
#define _NET_HANDLE_

#include "ut_net_define.h"

__C_BEGIN_DECLS

int32_t		init_net_handle(struct ut_net_t* net);
void		uninit_net_handle(struct ut_net_t* net);
int32_t		do_deliver_socket(struct ut_net_t* net, struct ut_channel_t* channel);

/************************************************************************
* 申请通道资源
************************************************************************/
struct ut_channel_t*	ut_channel_malloc(struct ut_net_t* net);

/************************************************************************
* 释放通道资源
************************************************************************/
void			ut_channel_free(struct ut_channel_t* channel);

/************************************************************************
* 初始化通道
************************************************************************/
struct ut_channel_t*		ut_channel_create(
	int32_t idx, struct ut_net_t* net);
void	ut_channel_delete(struct ut_channel_t* channel);

/************************************************************************
* 释放通道
************************************************************************/
void	ut_channel_finalize(struct ut_channel_t* channel);

__C_END_DECLS

#endif
