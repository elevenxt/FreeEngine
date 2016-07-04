/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#include "ut_net_listener.h"
#include "ut_defines.h"


ut_sock_t			ut_net_open_listener(const char* ip, int32_t port)
{
	int32_t nerr = 0;
	ut_sock_t listener = ut_sock_tcp();
	if(!ut_sock_isvalidate(listener)) return listener;
	UT_VERIFY_TRUE(ut_sock_reuseaddr(listener) == 0);
	nerr = ut_sock_bind(listener, ip, port);
	UT_CHECK_TRUE(nerr == 0);
	nerr = ut_sock_set_nonblock(listener);
	UT_CHECK_TRUE(nerr == 0);
	nerr = ut_sock_listen(listener, 128);
	UT_CHECK_TRUE(nerr == 0);

	return listener;

FAIL:
	ut_net_close_listener(listener);
	return ut_sock_invalid();
}

void			ut_net_close_listener(ut_sock_t listener)
{
	ut_sock_close(listener);
}

ut_sock_t		ut_net_accept_newsock(ut_sock_t listener)
{
	return ut_sock_accept(listener); 
}
