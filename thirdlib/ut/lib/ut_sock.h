/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



 
#ifndef _UT_SOCK_H_
#define _UT_SOCK_H_

// 这个模块还未测试

#include "ut_def.h"

__C_BEGIN_DECLS

#ifdef UT_PLATFORM_WINDOWS
typedef int32_t	ut_sock_t;
#endif
#ifdef UT_PLATFORM_LINUX
typedef int32_t		ut_sock_t;
#endif

int32_t		ut_net_init();
void		ut_net_cleanup();

int32_t			ut_net_ip(const char* ip);
int16_t	ut_net_port(int16_t port);

ut_sock_t	ut_sock_tcp();
ut_sock_t	ut_sock_udp();
ut_sock_t	ut_sock_invalid();
int32_t ut_sock_close(ut_sock_t sock);

int32_t ut_sock_shutdown(ut_sock_t sock);
int32_t ut_sock_set_nonblock(ut_sock_t sock);
int32_t ut_sock_bind(ut_sock_t sock, const char* ip, int32_t port);
int32_t ut_sock_bind_i(ut_sock_t sock, int32_t ip, int32_t port);
int32_t ut_sock_connect(ut_sock_t sock, const char* ip, int32_t port);
int32_t ut_sock_connect_i(ut_sock_t sock, int32_t ip, int32_t port);
int32_t ut_sock_listen(ut_sock_t sock, int32_t que);
ut_sock_t		ut_sock_accept(ut_sock_t sock);
int32_t ut_sock_isvalidate(ut_sock_t sock);

int32_t ut_sock_set_sendbuf_size(ut_sock_t sock, int32_t size);
int32_t ut_sock_set_recvbuf_size(ut_sock_t sock, int32_t size);
int32_t ut_sock_set_keepalive(ut_sock_t sock);
int32_t ut_sock_getpeer_info(ut_sock_t sock, int32_t* ip, int32_t* port);
int32_t ut_sock_getsock_info(ut_sock_t sock, int32_t* ip, int32_t* port);
int32_t ut_sock_lasterror();

int32_t ut_sock_send(ut_sock_t sock, const char* data, int32_t size);
int32_t ut_sock_recv(ut_sock_t sock, char* data, int32_t size);
int32_t ut_sock_sendto(ut_sock_t sock, int32_t ip, int32_t port, const char* data, int32_t size);
int32_t ut_sock_recvfrom(ut_sock_t sock, int32_t ip, int32_t port, char* data, int32_t size);

int32_t ut_sock_reuseaddr(ut_sock_t sock);

__C_END_DECLS



#endif
