/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/




#include "ut_sock.h"
#include <memory.h>

#include "ut_memory.h"
#include "ut_defines.h"
#include "ut_net_util.h"

#ifdef UT_PLATFORM_LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#ifdef UT_PLATFORM_WINDOWS
#include <WinSock2.h>
#include <mstcpip.h>
#include <Mswsock.h>
typedef int32_t socklen_t;
#endif

#ifdef UT_PLATFORM_WINDOWS
int32_t ut_net_init()
{
	WSADATA wsa_data;
	return WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0 ? 0 : -ut_lasterror();
}

void ut_net_cleanup()
{
	WSACleanup();
}
#endif

#ifdef UT_PLATFORM_LINUX
int32_t ut_net_init()
{
	return 0;
}

void ut_net_cleanup()
{

}
#endif

static ut_sock_t	ut_sock_create(int32_t type, int32_t protocol)
{
	return socket(AF_INET, type, protocol);
}

ut_sock_t	ut_sock_tcp()
{
	return ut_sock_create(SOCK_STREAM, IPPROTO_TCP);
}

ut_sock_t	ut_sock_udp()
{
	return ut_sock_create(SOCK_DGRAM, IPPROTO_UDP);
}

ut_sock_t	ut_sock_invalid()
{
	return INVALID_SOCKET;
}

#ifdef UT_PLATFORM_LINUX
int32_t ut_sock_close(ut_sock_t sock)
{
	return 0 == close(sock)?0:-ut_lasterror();
}
#endif

#ifdef UT_PLATFORM_WINDOWS
int32_t ut_sock_close(ut_sock_t sock)
{
	return 0 == closesocket(sock) ? 0 : -ut_lasterror();
}
#endif

#ifdef UT_PLATFORM_LINUX
int32_t ut_sock_shutdown(ut_sock_t sock)
{
	return shutdown(sock, SHUT_RDWR) == 0?0:-ut_lasterror();
}
#endif
#ifdef UT_PLATFORM_WINDOWS
int32_t ut_sock_shutdown(ut_sock_t sock)
{
	return shutdown(sock, 2) == 0 ? 0 : -ut_lasterror();
}
#endif

#ifdef UT_PLATFORM_WINDOWS
int32_t ut_sock_set_nonblock(ut_sock_t sock)
{
	unsigned long ul = 1;
	return ioctlsocket(sock, FIONBIO, (unsigned long*)&ul) == 0 ? 0 : -ut_lasterror();
}
#endif
#ifdef UT_PLATFORM_LINUX
int32_t ut_sock_set_nonblock(ut_sock_t sock)
{
	int32_t err = -1;
	err = fcntl(sock, F_GETFL, 0);
	if (err == -1)
	{
		return -ut_lasterror();
	}
	err = fcntl(sock, F_SETFL, err | O_NONBLOCK);

	return (err == -1)?-ut_lasterror():0;
}
#endif

int32_t	 ut_net_ip(const char* ip)
{
	if (ip == 0)
	{
		return 0;
	}
	else
	{
		return (int32_t)inet_addr(ip);
	}
}

int16_t	ut_net_port(int16_t port)
{
	return htons(port);
}

struct sockaddr_in ut_ip4_addr(const char* ip, int32_t port)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = ut_net_port((int16_t)port);
	addr.sin_addr.s_addr = ut_net_ip(ip);
	
	return addr;
}

int32_t ut_sock_bind(ut_sock_t sock, const char* ip, int32_t port)
{
	struct sockaddr_in addr = ut_ip4_addr(ip, port);;
	return bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0 ? 0 : -ut_lasterror();
}

int32_t ut_sock_bind_i(ut_sock_t sock, int32_t ip, int32_t port)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = ut_net_port((int16_t)port);
	addr.sin_addr.s_addr = ip;

	return bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0 ? 0 : -ut_lasterror();
}

int32_t ut_sock_connect(ut_sock_t sock, const char* ip, int32_t port)
{
	struct sockaddr_in addr = ut_ip4_addr(ip, port);
	return connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0 ? 0 : -ut_lasterror();
}

int32_t ut_sock_connect_i(ut_sock_t sock, int32_t ip, int32_t port)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = ut_net_port((int16_t)port);
	addr.sin_addr.s_addr = ip;

	return connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0 ? 0 : -ut_lasterror();
}

int32_t ut_sock_listen(ut_sock_t sock, int32_t que)
{
	return listen(sock, que) == 0 ? 0 : -ut_lasterror();
}

ut_sock_t ut_sock_accept(ut_sock_t sock)
{
	return accept(sock, 0, 0);
}

int32_t ut_sock_isvalidate(ut_sock_t sock)
{
	return sock != ut_sock_invalid();
}

int32_t ut_sock_set_sendbuf_size(ut_sock_t sock, int32_t size)
{
	int32_t sizelen = sizeof(size);
	return setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&size, sizelen) == 0 ? 0 : -ut_lasterror();
}

int32_t ut_sock_set_recvbuf_size(ut_sock_t sock, int32_t size)
{
	int32_t sizelen = sizeof(size);
	return setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&size, sizelen) == 0 ? 0 : -ut_lasterror();
}

#ifdef UT_PLATFORM_WINDOWS
int32_t ut_sock_set_keepalive(ut_sock_t sock)
{
	int32_t nerr = SOCKET_ERROR;
	struct tcp_keepalive alive_in		= {0};
	struct tcp_keepalive alive_out		= {0};
	unsigned long bytes_return	= 0;
	int32_t nKeepAlive = 1;

	UT_VERIFY_TRUE (sock != 0);

	if (0 != setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&nKeepAlive, sizeof(nKeepAlive)))
	{
		return -ut_lasterror();
	}

	alive_in.keepalivetime		= 5000;
	alive_in.keepaliveinterval	= 2000;
	alive_in.onoff				= TRUE;
	bytes_return	= 0;

	nerr = WSAIoctl(sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in),
		&alive_out, sizeof(alive_out), &bytes_return, NULL, NULL);

FAIL:
	return nerr == 0 ? 0 : -ut_lasterror();
}
#endif
#ifdef UT_PLATFORM_LINUX
int32_t ut_sock_set_keepalive(ut_sock_t sock)
{
	// 设置保活定时器
	int32_t keepalive = 1;
	int32_t keepidle = 120;
	int32_t keepinterval = 5;
	int32_t keepcount = 4;
	int32_t err = 0;

	err = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (void*)&keepalive, sizeof(keepalive));
	if (0 != err) return -ut_lasterror();
	err = setsockopt(sock, SOL_TCP, TCP_KEEPIDLE, (void*)&keepidle, sizeof(keepidle));
	if (0 != err) return -ut_lasterror();
	err = setsockopt(sock, SOL_TCP, TCP_KEEPINTVL, (void*)&keepinterval, sizeof(keepinterval));
	if (0 != err) return -ut_lasterror();
	err = setsockopt(sock, SOL_TCP, TCP_KEEPCNT, (void*)&keepcount, sizeof(keepcount));
	if (0 != err) return -ut_lasterror();

	int32_t on=1;
	err = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,&on,sizeof(on));  
	if (0 != err) return -ut_lasterror();

	return 0;
}
#endif

int32_t ut_sock_getpeer_info(ut_sock_t sock, int32_t* ip, int32_t* port)
{
	struct sockaddr_in addr;
	socklen_t		addrlen = 0;
	addrlen = sizeof(addr);
	memset(&addr, 0, addrlen);

	UT_VERIFY_TRUE (ip != 0);
	UT_VERIFY_TRUE (port != 0);

	*ip = 0;
	*port = 0;

	if (0 != getpeername(sock, (struct sockaddr*)&addr, &addrlen))
	{
		return -ut_lasterror();
	}

#ifdef UT_PLATFORM_WINDOWS
	*ip = addr.sin_addr.S_un.S_addr;
#else
	*ip = addr.sin_addr.s_addr;
#endif
	*port = ntohs(addr.sin_port);

	return 0;

FAIL:
	return -1;
}

int32_t ut_sock_getsock_info(ut_sock_t sock, int32_t* ip, int32_t* port)
{
	struct sockaddr_in addr;
	socklen_t		addrlen = 0;
	addrlen = sizeof(addr);
	memset(&addr, 0, addrlen);

	*ip = 0;
	*port = 0;

	UT_VERIFY_TRUE (ip != 0);
	UT_VERIFY_TRUE (port != 0);

	if (0 != getsockname(sock, (struct sockaddr*)&addr, &addrlen))
	{
		return -ut_lasterror();
	}

#ifdef UT_PLATFORM_WINDOWS
	*ip = addr.sin_addr.S_un.S_addr;
#else
	*ip = addr.sin_addr.s_addr;
#endif
	*port = ntohs(addr.sin_port);

	return 0;

FAIL:
	return -1;
}

#ifdef UT_PLATFORM_WINDOWS
int32_t	ut_sock_lasterror()
{
	return WSAGetLastError();
}
#else
int32_t	ut_sock_lasterror()
{
	return ut_lasterror();
}
#endif

int32_t ut_sock_send(ut_sock_t sock, const char* data, int32_t size)
{
	int32_t nerr = -1;

#ifdef UT_PLATFORM_LINUX
	nerr = send(sock, data, size, MSG_NOSIGNAL);
#endif
#ifdef UT_PLATFORM_WINDOWS
	nerr = send(sock, data, size, 0);
#endif

	return nerr >= 0 ? nerr : -ut_lasterror();
}

int32_t ut_sock_recv(ut_sock_t sock, char* data, int32_t size)
{
	int32_t nerr = -1;

	if (data == 0 || size <= 0)
	{
		return -1;
	}
	
#ifdef UT_PLATFORM_LINUX
	nerr = recv(sock, data, size, MSG_NOSIGNAL);
#endif
#ifdef UT_PLATFORM_WINDOWS
	nerr = recv(sock, data, size, 0);
#endif

	return nerr >= 0 ? nerr : -ut_lasterror();
}

int32_t ut_sock_sendto(ut_sock_t sock, int32_t ip, int32_t port, const char* data, int32_t size)
{
	struct sockaddr_in addr;
	int32_t nerr = -1;
	
	if (data == 0 || size <= 0)
	{
		return -1;
	}

	memset((void*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = ip;

#ifdef UT_PLATFORM_LINUX
	nerr = sendto(sock, data, size, MSG_NOSIGNAL, (struct sockaddr*)&addr, sizeof(addr));
#endif
#ifdef UT_PLATFORM_WINDOWS
	nerr = sendto(sock, data, size, 0, (struct sockaddr*)&addr, sizeof(addr));
#endif

	return nerr >= 0 ? nerr : -ut_lasterror();
}

int32_t ut_sock_recvfrom(ut_sock_t sock, int32_t ip, int32_t port, char* data, int32_t size)
{
	struct sockaddr_in addr;
	socklen_t  addrlen = sizeof(addr);
	int32_t nerr = -1;

	if (data == 0 || size <= 0)
	{
		return -1;
	}

	memset((void*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = ut_net_port(port);
	addr.sin_addr.s_addr = ip;

#ifdef UT_PLATFORM_LINUX
	nerr = recvfrom(sock, data, size, MSG_NOSIGNAL, (struct sockaddr*)&addr, &addrlen);
#endif
#ifdef UT_PLATFORM_WINDOWS
	nerr = recvfrom(sock, data, size, 0, (struct sockaddr*)&addr, &addrlen);
#endif

	return nerr >= 0 ? nerr : -ut_lasterror();
}

int32_t ut_sock_reuseaddr(ut_sock_t sock)
{
	int32_t reuseaddr = 1;
	return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseaddr, sizeof(reuseaddr)) == 0 ? 0 : -ut_lasterror();
}
