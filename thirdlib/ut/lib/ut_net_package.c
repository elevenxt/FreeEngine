/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#include <memory.h>
#include "ut_net_package.h"
#include "ut_net.h"
#include "ut_net_define.h"
#include "ut_memory.h"
#include "ut_defines.h"

struct ut_pkgnet_t;

static const int32_t PACK_LEN_SIZE = 2;

struct ut_pkgnet_config_t
{
	struct ut_net_config_t	raw_cfg;
	int32_t max_package;
};

struct ut_pkgchannel_t
{
	struct ut_channel_t		raw_channel;
	recv_pkg_data			rcv_func;	
	int32_t		write_pos;
	char		recv_buf[];
};

struct ut_pkgnet_t
{
	struct ut_net_t				raw_net;
	struct ut_pkgnet_config_t	cfg;
	new_pkg_connection			new_func;
	lost_pkg_connection			lost_func;
	char*						send_buf;
	int32_t						send_buf_size;
};

static struct ut_pkgnet_config_t defcfg =
{
	{
		sizeof(struct ut_pkgnet_t),
		sizeof(struct ut_pkgchannel_t),
		1024,
	},
	1024,
};

static void _new_connection(struct ut_channel_t* channel, void* netdata, void* channeldata)
{
	struct ut_pkgchannel_t* pchannel = (struct ut_pkgchannel_t*)channel;
	struct ut_pkgnet_t* net = (struct ut_pkgnet_t*)channel->net;

	UT_VERIFY_TRUE(pchannel->rcv_func == 0);
	UT_VERIFY_TRUE(pchannel->write_pos == 0);

	net->new_func(pchannel, netdata, channeldata);

FAIL:
	return;
}

static void _lost_connection(struct ut_channel_t* channel, void* netdata, void* channeldata)
{
	struct ut_pkgchannel_t* pchannel = (struct ut_pkgchannel_t*)channel;
	struct ut_pkgnet_t* net = (struct ut_pkgnet_t*)channel->net;

	net->lost_func(pchannel, netdata, channeldata);

	pchannel->rcv_func = 0;
	pchannel->write_pos = 0;
}

static void _recv_data(struct ut_channel_t* channel, const char* data
	, int32_t datalen, void* netdata, void* channeldata)
{
	int32_t packpos = 0;
	int16_t packlen = 0;
	struct ut_pkgchannel_t* pchannel = (struct ut_pkgchannel_t*)channel;
	struct ut_pkgnet_t* net = (struct ut_pkgnet_t*)channel->net;
	UT_VERIFY_TRUE(channel != 0);
	UT_VERIFY_TRUE(pchannel != 0);	
	UT_VERIFY_TRUE(data != 0 && datalen > 0);

	if (pchannel->write_pos > 0)
	{
		int32_t cplen = 0;
		if (pchannel->write_pos == 1)
		{
			pchannel->recv_buf[1] = data[0];
			packpos++;
			pchannel->write_pos++;
		}
		packlen = *(int16_t*)pchannel->recv_buf;
		UT_VERIFY_TRUE(packlen <= net->cfg.max_package+sizeof(int16_t));
		UT_VERIFY_TRUE(packlen > sizeof(int16_t));
		/*如果上次有残留的数据，必定是半包*/
		UT_VERIFY_TRUE(packlen > pchannel->write_pos);
		/*将这个半包，拼成一个整包*/
		cplen = packlen - pchannel->write_pos;
		if (cplen > datalen-packpos)
		{
			cplen = datalen - packpos;
		}
		memcpy(pchannel->recv_buf+pchannel->write_pos, data+packpos, cplen);
		packpos += cplen;
		pchannel->write_pos += cplen;
		UT_VERIFY_TRUE(pchannel->write_pos <= packlen);
		if (pchannel->write_pos != packlen)
		{
			UT_VERIFY_TRUE(packpos == datalen);
			return;
		}

		pchannel->rcv_func(pchannel, pchannel->recv_buf + sizeof(int16_t),
			packlen - sizeof(int16_t), netdata, channeldata);
		pchannel->write_pos = 0;
	}
	UT_VERIFY_TRUE(packpos <= datalen);
	while (packpos < datalen)
	{
		UT_VERIFY_TRUE(pchannel->write_pos == 0);
		int32_t left = datalen - packpos;
		if (left < sizeof(int16_t))
		{
			break;
		}
		packlen = *(int16_t*)(data + packpos);
		UT_VERIFY_TRUE(packlen <= net->cfg.max_package + sizeof(int16_t));
		UT_VERIFY_TRUE(packlen > sizeof(int16_t));
		if (packlen > left)
		{
			break;
		}
		UT_VERIFY_TRUE(packlen > sizeof(int16_t));

		pchannel->rcv_func(pchannel, data + packpos + sizeof(int16_t),
			packlen - sizeof(int16_t), netdata, channeldata);

		packpos += packlen;
	}
	UT_VERIFY_TRUE(packpos <= datalen);
	if (packpos < datalen)
	{
		memcpy(pchannel->recv_buf, data + packpos, datalen - packpos);
		pchannel->write_pos = datalen-packpos;
	}

	return;

FAIL:
	ut_pkgnet_channel_close(pchannel);
	return;
}

struct ut_pkgnet_config_t*	ut_pkgnet_config_create()
{
	struct ut_pkgnet_config_t* cfg = UT_NEW(struct ut_pkgnet_config_t);
	if (cfg != 0) *cfg = defcfg;
	return cfg;
}

void	ut_pkgnet_config_delete(struct ut_pkgnet_config_t* cfg)
{
	UT_DELETE(cfg);
}

int32_t		ut_pkgnet_config_set_connectionlimit(struct ut_pkgnet_config_t* cfg, int32_t limit)
{
	UT_VERIFY_TRUE(cfg != 0);
	return ut_net_config_set_connectionlimit(&cfg->raw_cfg, limit);

FAIL:
	return -1;
}

int32_t		ut_pkgnet_config_set_maxpackage(struct ut_pkgnet_config_t* cfg, int32_t value)
{
	UT_VERIFY_TRUE(cfg != 0);
	UT_VERIFY_TRUE(value > 0);

	cfg->max_package = value;
	return 0;

FAIL:
	return -1;
}

struct ut_pkgnet_t*		ut_pkgnet_create(struct ut_pkgnet_config_t* cfg,
	new_pkg_connection newfunc, lost_pkg_connection lostfunc, void* data)
{
	struct ut_pkgnet_t* net = 0;	
	if (cfg == 0)
	{
		cfg = &defcfg;
	}

	UT_VERIFY_TRUE(cfg->max_package > 0);
	UT_VERIFY_TRUE(cfg->raw_cfg.st_net_size >= sizeof(struct ut_pkgnet_t));
	UT_VERIFY_TRUE(cfg->raw_cfg.st_channel_size >= sizeof(struct ut_pkgchannel_t));
	cfg->raw_cfg.st_channel_size += cfg->max_package+sizeof(int16_t);

	net = (struct ut_pkgnet_t*)ut_net_create((struct ut_net_config_t*)cfg, _new_connection, _lost_connection, data);
	UT_VERIFY_TRUE(net != 0);

	net->cfg = *cfg;
	net->new_func = newfunc;
	net->lost_func = lostfunc;
	net->send_buf_size = cfg->max_package + sizeof(int16_t);
	net->send_buf = UT_NEW_ARRAY(char, net->send_buf_size);
	UT_VERIFY_TRUE(net->send_buf != 0);	

	return net;

FAIL:
	if (net != 0)
	{
		ut_pkgnet_delete(net);
	}

	return 0;
}

void	ut_pkgnet_delete(struct ut_pkgnet_t* net)
{
	UT_VERIFY_TRUE(net != 0);
	UT_DELETE(net->send_buf);
	ut_net_delete((struct ut_net_t*)net);

FAIL:
	return;
}

int32_t		ut_pkgnet_send(struct ut_pkgchannel_t* channel, const char* data, unsigned short len)
{
	const char* dam[]={data};
	int32_t lenm[]={len};
	return ut_pkgnet_send_m(channel, 1, dam, lenm);
}

int32_t		ut_pkgnet_send_m(struct ut_pkgchannel_t* channel, int32_t blocknum, const char* data[], int32_t len[])
{
	int32_t i = 0;
	struct ut_channel_t* raw_channel = 0;
	struct ut_net_t* raw_net = 0;
	struct ut_pkgnet_t* net = 0;

	unsigned short datalen = sizeof(datalen);
	unsigned short sendlen = 0;

	/*get send buffer*/
	UT_VERIFY_TRUE(channel != 0);
	raw_channel = (struct ut_channel_t*)channel;

	UT_VERIFY_TRUE(raw_channel != 0);
	raw_net = raw_channel->net;
	UT_VERIFY_TRUE(raw_net != 0);
	net = (struct ut_pkgnet_t*)raw_net;
	UT_VERIFY_TRUE(net != 0);

	UT_VERIFY_TRUE(blocknum>0);
	for(i=0; i<blocknum; i++)
	{
		UT_VERIFY_TRUE(data[i] != 0 && len[i]>0);
		UT_VERIFY_TRUE(datalen+len[i]<=net->send_buf_size);
		memcpy(net->send_buf+datalen, data[i], len[i]);
		datalen += len[i];
	}
		
	*(unsigned short*)(net->send_buf) = datalen;
	sendlen = ut_net_send(raw_channel, net->send_buf, datalen);
	if (sendlen != datalen)
	{
		ut_pkgnet_channel_close(channel);
		return -1;
	}

	return 0;

FAIL:
	return -1;
}

int32_t		ut_pkgnet_pool_once(struct ut_pkgnet_t* net, int32_t weight, int32_t waittime)
{
	UT_VERIFY_TRUE(net != 0);
	return ut_net_pool_once((struct ut_net_t*)net, weight, waittime);

FAIL:
	return -1;
}

void	ut_pkgnet_channel_close(struct ut_pkgchannel_t* channel)
{
	UT_VERIFY_TRUE(channel != 0);
	ut_net_channel_close((struct ut_channel_t*)channel);

FAIL:
	return;
}

struct ut_pkgchannel_t*	ut_pkgnet_deliver_socket(struct ut_pkgnet_t* net, ut_sock_t sock,
	recv_pkg_data rcvfunc, void* data)
{
	struct ut_pkgchannel_t* channel = 0;
	UT_VERIFY_TRUE(net != 0);
	channel = (struct ut_pkgchannel_t*)ut_net_deliver_socket((struct ut_net_t*)net, sock, _recv_data, data);
	UT_CHECK_TRUE(channel != 0);
	channel->rcv_func = rcvfunc;
	return channel;

FAIL:
	return 0;
}

int32_t		ut_pkgnet_channel_index(struct ut_pkgchannel_t* channel)
{
	UT_VERIFY_TRUE(channel != 0);
	return ut_net_channel_index((struct ut_channel_t*)channel);
	
FAIL:
	return -1;
}

int32_t		ut_pkgnet_channel_getname(struct ut_pkgchannel_t* channel, int32_t* ip, int32_t* port)
{
	UT_VERIFY_TRUE(channel != 0 && ip != 0 && port != 0);
	return ut_net_channel_getname((struct ut_channel_t*)channel, ip, port);
FAIL:
	return -1;
}

int32_t		ut_pkgnet_channel_getpeer(struct ut_pkgchannel_t* channel, int32_t* ip, int32_t* port)
{
	UT_VERIFY_TRUE(channel != 0 && ip != 0 && port != 0);
	return ut_net_channel_getpeer((struct ut_channel_t*)channel, ip, port);
FAIL:
	return -1;
}

