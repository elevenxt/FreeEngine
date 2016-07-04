/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#ifndef _UT_NET_PACKAGE_
#define _UT_NET_PACKAGE_

#include "ut_def.h"
#include "ut_sock.h"

__C_BEGIN_DECLS

struct ut_pkgnet_config_t;
struct ut_pkgnet_t;
struct ut_pkgchannel_t;

typedef void(*new_pkg_connection)	(struct ut_pkgchannel_t* channel, void* netdata, void* channeldata);
typedef void(*lost_pkg_connection)	(struct ut_pkgchannel_t* channel, void* netdata, void* channeldata);
typedef void(*recv_pkg_data)		(struct ut_pkgchannel_t* channel, const char* data
	, int32_t datalen, void* netdata, void* channeldata);

struct ut_pkgnet_config_t*	ut_pkgnet_config_create();
void	ut_pkgnet_config_delete(struct ut_pkgnet_config_t* cfg);
int32_t		ut_pkgnet_config_set_connectionlimit(struct ut_pkgnet_config_t* cfg, int32_t limit);
int32_t		ut_pkgnet_config_set_maxpackage(struct ut_pkgnet_config_t* cfg, int32_t value);

struct ut_pkgnet_t*		ut_pkgnet_create(struct ut_pkgnet_config_t* cfg, new_pkg_connection newfunc,
	lost_pkg_connection lostfunc, void* data);
void	ut_pkgnet_delete(struct ut_pkgnet_t* net);

int32_t		ut_pkgnet_send(struct ut_pkgchannel_t* channel, const char* data, unsigned short len);
int32_t		ut_pkgnet_send_m(struct ut_pkgchannel_t* channel, int32_t blocknum, const char* data[], int32_t len[]);

int32_t		ut_pkgnet_pool_once(struct ut_pkgnet_t* net, int32_t weight, int32_t waittime);

void	ut_pkgnet_channel_close(struct ut_pkgchannel_t* channel);

struct ut_pkgchannel_t*	ut_pkgnet_deliver_socket(struct ut_pkgnet_t* net, ut_sock_t sock,
	recv_pkg_data rcvfunc, void* data);

int32_t		ut_pkgnet_channel_index(struct ut_pkgchannel_t* channel);

int32_t		ut_pkgnet_channel_getname(struct ut_pkgchannel_t* channel, int32_t* ip, int32_t* port);
int32_t		ut_pkgnet_channel_getpeer(struct ut_pkgchannel_t* channel, int32_t* ip, int32_t* port);

__C_END_DECLS

#endif
