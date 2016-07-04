
#include <inttypes.h>

#include "ut_net.h"
#include "ut_net_listener.h"
#include "ut_thread.h"
#include "ut_time.h"
#include "ut_math.h"
#include "stdio.h"
#include "stdlib.h"

#ifdef __linux__
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <assert.h>
#else
#include <Windows.h>
#include <assert.h>
#endif

static const char* server_ip = "127.0.0.1";
static int32_t server_port = 9001;

static char buffer[64 * 1024] = { 0 };

static int32_t serv_recvbyte = 0;
static int32_t serv_recvpack = 0;
static int32_t serv_connnum = 0;

static int32_t cli_recvbyte = 0;
static int32_t cli_recvpack = 0;
static int32_t cli_connnum = 0;

static void serv_new_connection(struct ut_channel_t* channel, void* netdata, void* channeldata)
{
	serv_connnum++;
}

static void serv_lost_connection(struct ut_channel_t* channel, void* netdata, void* channeldata)
{
	serv_connnum--;
}

static void serv_rcv_data(struct ut_channel_t* channel, const char* data
	, int32_t datalen, void* netdata, void* channeldata)
{
	serv_recvbyte += datalen;
	serv_recvpack++;
	ut_net_send(channel, data, datalen);
}

static int32_t server_thread(void* param)
{
	struct ut_net_t* net;

	int64_t bt = 0;
	int64_t et = 0;
	ut_sock_t		listener = 0;

	listener = ut_net_open_listener(server_ip, server_port);
	if (!ut_sock_isvalidate(listener))
	{
		printf("open listener error.\r\n");
		return 0;
	}

	net = ut_net_create(0, serv_new_connection, serv_lost_connection, 0);
	if (net == 0)
	{
		printf("open net failed.\r\n");
		return 0;
	}

	bt = ut_gettickcount();
	et = ut_gettickcount();

	while (1)
	{
		ut_sock_t new_sock = ut_sock_invalid();

		ut_net_pool_once(net, 1024, 1);

		while ((new_sock = ut_sock_accept(listener)) != ut_sock_invalid())
		{
			if (0 == ut_net_deliver_socket(net, new_sock, serv_rcv_data, 0))
			{
				printf("deliver socket failed.\r\n");
			}
		}

		et = ut_gettickcount();
		if (et / 1000 != bt / 1000)
		{
			printf("server_connnum:%d\tspeed:%5.2fMBps\tpack num:%dpps.\r\n"
				, serv_connnum, serv_recvbyte / 1024.0f / 1024.0f, serv_recvpack);

			serv_recvbyte = 0;
			serv_recvpack = 0;
			bt = et;
		}
	}

	return 0;
}

static void cli_new_connection(struct ut_channel_t* channel, void* netdata, void* channeldata)
{
	cli_connnum++;
	ut_net_send(channel, buffer, 65536);
}

static void cli_lost_connection(struct ut_channel_t* channel, void* netdata, void* channeldata)
{
	cli_connnum--;
}

static void cli_rcv_data(struct ut_channel_t* channel, const char* data
	, int32_t datalen, void* netdata, void* channeldata)
{
	cli_recvbyte += datalen;
	cli_recvpack++;
	ut_net_send(channel, data, datalen);
}

static int32_t client_thread(void* param)
{
	int32_t i = 0;
	struct ut_net_t* net;

	int64_t bt = 0;
	int64_t et = 0;

	net = ut_net_create(0, cli_new_connection, cli_lost_connection, 0);
	if (net == 0)
	{
		printf("open net failed.\r\n");
		return 0;
	}

	for (i = 0; i < 1000; i++)
	{
		ut_sock_t sock = ut_sock_tcp();
		if (!ut_sock_isvalidate(sock))
		{
			printf("create tcp sock failed.\r\n");
			continue;
		}
		int32_t err = ut_sock_connect(sock, server_ip, server_port);
		if (err != 0)
		{
			printf("connect to server failed.%d\r\n", -err);
			ut_sock_close(err);
			continue;
		}
		if (0 == ut_net_deliver_socket(net, sock, cli_rcv_data, 0))
		{
			printf("deliver socket failed.\r\n");
		}
	}

	bt = ut_gettickcount();
	et = ut_gettickcount();

	while (1)
	{
		ut_net_pool_once(net, 1024, 1);

		et = ut_gettickcount();
		if (et / 1000 != bt / 1000)
		{
			printf("server_connnum:%d\tspeed:%5.2fMBps\tpack num:%dpps.\r\n"
				, cli_connnum, cli_recvbyte / 1024.0f / 1024.0f, cli_recvpack);

			cli_recvbyte = 0;
			cli_recvpack = 0;
			bt = et;
		}
	}

	return 0;
}

int32_t ut_net_test()
{
	ut_thread_t* cthread = 0;
	ut_thread_t* sthread = 0;
	
	ut_net_init();

#ifdef __linux__
	struct rlimit rlim;
	rlim.rlim_max=65536;
	rlim.rlim_cur = 65536;
	if (0 == setrlimit(RLIMIT_NOFILE, &rlim))
	{
		printf("set limit file to 65536\r\n");
	}
#endif

	cthread = ut_thread_new(client_thread, 0);
	sthread = ut_thread_new(server_thread, 0);

	for (;;)
	{
		ut_sleep(1);
	}	
	
	ut_thread_delete(cthread);
	ut_thread_delete(sthread);

	return 0;

}
