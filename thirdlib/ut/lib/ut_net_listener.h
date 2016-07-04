/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#ifndef _UT_NET_LISTENER_
#define _UT_NET_LISTENER_

#include "ut_def.h"
#include "ut_sock.h"

__C_BEGIN_DECLS


ut_sock_t		ut_net_open_listener(const char* ip, int32_t port);
void			ut_net_close_listener(ut_sock_t listener);
ut_sock_t		ut_net_accept_newsock(ut_sock_t listener);

__C_END_DECLS

#endif

