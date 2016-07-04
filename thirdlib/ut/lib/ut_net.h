/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#ifndef _NET_LIB_
#define _NET_LIB_

#include "ut_def.h"
#include "ut_sock.h"

__C_BEGIN_DECLS

struct ut_net_config_t;
struct ut_net_t;
struct ut_channel_t;

typedef void(*new_connection)	(struct ut_channel_t* channel, void* netdata, void* channeldata);
typedef void(*lost_connection)	(struct ut_channel_t* channel, void* netdata, void* channeldata);
typedef void(*recv_data)		(struct ut_channel_t* channel, const char* data
	, int32_t datalen, void* netdata, void* channeldata);

struct ut_net_config_t*	ut_net_config_create();
void					ut_net_config_delete(struct ut_net_config_t* cfg);
int32_t		ut_net_config_set_connectionlimit(struct ut_net_config_t* cfg, int32_t limit);

struct ut_net_t*		ut_net_create(struct ut_net_config_t* cfg, new_connection newfunc, 
										lost_connection lostfunc, void* data);
void		ut_net_delete(struct ut_net_t* net);

int32_t		ut_net_send(struct ut_channel_t* channel, const char* data, int32_t datalen);

int32_t		ut_net_pool_once(struct ut_net_t* net, int32_t weight, int32_t waittime);

void		ut_net_channel_close(struct ut_channel_t* channel);

struct ut_channel_t*	ut_net_deliver_socket(struct ut_net_t* net, ut_sock_t sock, 
												recv_data rcvfunc, void* data);

int32_t		ut_net_channel_index(struct ut_channel_t* channel);

int32_t		ut_net_channel_getname(struct ut_channel_t* channel, int32_t* ip, int32_t* port);
int32_t		ut_net_channel_getpeer(struct ut_channel_t* channel, int32_t* ip, int32_t* port);

__C_END_DECLS

#endif
