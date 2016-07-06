/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_def.h"

#ifdef UT_PLATFORM_WINDOWS

#include "ut_net_util.h"
#include "ut_net_handle.h"


enum
{
	POST_IO = 0xFFFFFFFF,
	IO_TYPE_NEW_CONNECTION = 1,
};

int32_t init_net_handle(struct ut_net_t* net)
{
	int32_t err = 0;
	WSADATA wsa_data;
	UT_VERIFY_TRUE(0 == WSAStartup(MAKEWORD(2, 2), &wsa_data));

	net->io_complete_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	UT_VERIFY_TRUE(0 != net->io_complete_port);

	return 0;

FAIL:
	err = -ut_wsalasterror();
	WSACleanup();
	return err;
}

void uninit_net_handle(struct ut_net_t* net)
{
	UT_VERIFY_TRUE(net != 0);
	CloseHandle(net->io_complete_port);
	net->io_complete_port = 0;

	WSACleanup();

FAIL:
	return;
}

int32_t do_deliver_socket(struct ut_net_t* net, struct ut_channel_t* channel)

{
	int32_t err = 0;
	
	int32_t send_buf_size = 0;
	int32_t sbs_len = 0;
	int32_t rcv_buf_size = 0;
	int32_t rbs_len = 0;
	
	HANDLE hioPort = INVALID_HANDLE_VALUE;

	memset(&channel->io_overlapped.overlapped, 0, sizeof(OVERLAPPED));
	channel->io_overlapped.io_type = IO_RECEIVE;
	channel->io_overlapped.wsabuf.buf = 0;
	channel->io_overlapped.wsabuf.len = 0;

	hioPort = CreateIoCompletionPort((HANDLE)channel->sock, net->io_complete_port, (DWORD)channel, 0);
	UT_CHECK_TRUE (hioPort == net->io_complete_port);
	
	UT_CHECK_TRUE(PostQueuedCompletionStatus(net->io_complete_port, POST_IO, (DWORD)channel, &channel->io_overlapped.overlapped));

	return 0;

FAIL:
	return -ut_wsalasterror();
}

int32_t do_sync_recv(struct ut_net_t* net, struct ut_channel_t* channel)
{
	DWORD io_size = 0;
	ULONG flags = 0;
	int32_t ret_val = 0;


	memset(&channel->io_overlapped.overlapped, 0, sizeof(OVERLAPPED));
	channel->io_overlapped.wsabuf.buf = channel->rcv_buf;
	channel->io_overlapped.wsabuf.len = OVERLAPPED_BUF_SIZE;

	io_size = 0;
	flags = MSG_PARTIAL;

	ret_val = WSARecv(channel->sock, &channel->io_overlapped.wsabuf, 1
		, &io_size, &flags, &channel->io_overlapped.overlapped, NULL);
	if ((ret_val == SOCKET_ERROR) && (WSAGetLastError() != WSA_IO_PENDING))
	{
		return -ut_wsalasterror();
	}

	return 0;
}

static void do_lost_connection(struct ut_channel_t* channel)
{
	UT_VERIFY_TRUE(0 != channel);
	UT_VERIFY_TRUE(0 != channel->net);

	channel->net->lost_func(channel, channel->net->user_data, channel->user_data);
	ut_sock_close(channel->sock);
	channel->sock = ut_sock_invalid();
	ut_channel_free(channel);

FAIL:
	return;
}

int32_t ut_net_pool_once(struct ut_net_t* net, int32_t weight, int32_t waittime)
{
	DWORD				io_size = 0;
	LPOVERLAPPED		overlapped = 0;
	IOOverlapped*		io_overlapped = 0;
	struct ut_channel_t*		channel = 0;
	BOOL ret = FALSE;
	DWORD io_error = 0;

	ret = GetQueuedCompletionStatus(net->io_complete_port
		, &io_size, (LPDWORD) &channel, &overlapped, 0);
	io_error = GetLastError();

	if (!ret)
	{
		if (io_error != WAIT_TIMEOUT)
		{
			if (channel == NULL || overlapped == NULL)
			{
				return io_error;
			}			
			else
			{
				do_lost_connection(channel);
			}
		}
		return io_error;
	}

	if (channel == NULL || overlapped == NULL)
	{
		return io_error;
	}

	io_overlapped = CONTAINING_RECORD(overlapped, IOOverlapped, overlapped);	
	UT_ASSERT_RV(&channel->io_overlapped == io_overlapped, -1);

	if (io_size == POST_IO)
	{
		if (0 != do_sync_recv(net, channel))
		{
			do_lost_connection(channel);
		}
		return io_error;
	}

	if (io_size==0 && channel->io_overlapped.io_type == IO_RECEIVE)
	{
		// Õý³£¹Ø±Õ
		do_lost_connection(channel);
		return io_error;
	}

	switch (io_overlapped->io_type)
	{
	case IO_RECEIVE :
		{
			channel->connection_data(channel, channel->rcv_buf,
				io_size, net->user_data, channel->user_data);
			if (0 != do_sync_recv(net, channel))
			{
				do_lost_connection(channel);
			}
		}
		break;	
	default:
		assert("can not run here");
		break;
	} 

	return io_error;
}


#endif
