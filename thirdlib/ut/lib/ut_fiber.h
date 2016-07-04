/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


// œÀ≥Ã°¢–≠≥Ãø‚£¨Œ¥≤‚ ‘
#ifndef _UT_FIBER_H_
#define _UT_FIBER_H_

#include "ut_def.h"

__C_BEGIN_DECLS

enum
{
	FIBER_RUNNING	= 2,
	FIBER_SUSPEND	= 3,
	FIBER_DEAD		= 4,
};

typedef struct ut_fiber	ut_fiber_t;
typedef struct ut_fiber_schedule	ut_fiber_schedule_t;

typedef void (*fiber_func)(void* ud);

ut_fiber_schedule_t*	ut_fiber_schedule_open();
void	ut_fiber_schedule_close(ut_fiber_schedule_t* schedule);

ut_fiber_t*	ut_fiber_create(ut_fiber_schedule_t* schedule, fiber_func func, int32_t stacksize, void* ud);
void	ut_fiber_delete(ut_fiber_schedule_t* schedule, ut_fiber_t* fiber);

ut_fiber_t*	ut_fiber_current(ut_fiber_schedule_t* schedule);
void	ut_fiber_switch(ut_fiber_schedule_t* schedule, ut_fiber_t* fiber);

int32_t	ut_fiber_state(ut_fiber_t* fiber);

__C_END_DECLS

#endif