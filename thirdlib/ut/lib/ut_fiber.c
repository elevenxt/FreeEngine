/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_fiber.h"
#include "ut_defines.h"
#include "ut_memory.h"
#include <stdint.h>
#include <string.h>

#ifdef UT_PLATFORM_WINDOWS
#include <windows.h>
#endif

#ifdef UT_PLATFORM_LINUX
#include <ucontext.h>
#endif

enum
{
	FIBER_INIT_CAP = 1024,
};

struct ut_fiber
{
	struct ut_fiber_schedule*	schedule;
#ifdef UT_PLATFORM_WINDOWS
	void*	fiber;
#endif
#ifdef UT_PLATFORM_LINUX
	ucontext_t	fiber;
	char*	szstack;
#endif

	fiber_func	ufunc;
	void*	ud;
	int32_t		index;
	int32_t		state;
};

struct ut_fiber_schedule
{
	struct ut_fiber**	fibers;
	int32_t			cap;
	int32_t			ncur;
};

#ifdef UT_PLATFORM_WINDOWS
static VOID WINAPI fiberStartRoutine(LPVOID lpFiber)
{
	struct ut_fiber*	fiber = (struct ut_fiber*)(lpFiber);

	fiber->ufunc(fiber->ud);
	fiber->state = FIBER_DEAD;

	ut_fiber_switch(fiber->schedule, fiber->schedule->fibers[0]);
}
#endif

#ifdef UT_PLATFORM_LINUX
static void fiberStartRoutine(uint32_t low32, uint32_t hi32)
{
	uintptr_t lpFiber = (uintptr_t)low32 | ((uintptr_t)hi32 << 32);
	struct ut_fiber*	fiber = (struct ut_fiber*)(lpFiber);

	fiber->ufunc(fiber->ud);
	fiber->state = FIBER_DEAD;

	ut_fiber_switch(fiber->schedule, fiber->schedule->fibers[0]);
}
#endif

void	ut_fiber_schedule_close(ut_fiber_schedule_t* schedule)
{
	if (schedule != 0)
	{
		if (schedule->fibers != 0)
		{
			int32_t i = 0;
			for (i=0; i<schedule->cap; i++)
			{
				if (schedule->fibers[i] != 0)
				{
					if (i>0)
					{
						ut_fiber_delete(schedule, schedule->fibers[i]);
					}
				}
			}
			UT_DELETE(schedule->fibers);
		}
		UT_DELETE(schedule);
	}
}

void	ut_fiber_switch(ut_fiber_schedule_t* schedule, ut_fiber_t* fiber)
{
	ut_fiber_t* curfiber = ut_fiber_current(schedule);

	UT_ASSERT_R (fiber->state != FIBER_DEAD);
	UT_ASSERT_R (fiber->index<schedule->cap && schedule->fibers[fiber->index] == fiber);

	schedule->ncur = fiber->index;

	if (curfiber->state != FIBER_DEAD)
	{
		curfiber->state = FIBER_SUSPEND;
	}
	fiber->state = FIBER_RUNNING;

#ifdef UT_PLATFORM_WINDOWS
	SwitchToFiber(fiber->fiber);
#endif
#ifdef UT_PLATFORM_LINUX
	swapcontext(&curfiber->fiber, &fiber->fiber);
#endif
}

ut_fiber_schedule_t*	ut_fiber_schedule_open()
{
	struct ut_fiber_schedule* schedule = UT_NEW(struct ut_fiber_schedule);
	UT_CHECK_TRUE(schedule != 0);

	schedule->fibers = UT_NEW_ARRAY(struct ut_fiber*, FIBER_INIT_CAP);
	UT_CHECK_TRUE(schedule->fibers != 0);
	schedule->cap = FIBER_INIT_CAP;

	schedule->fibers[0] = UT_NEW(struct ut_fiber);
	UT_CHECK_TRUE (0 != schedule->fibers[0]);

#ifdef UT_PLATFORM_WINDOWS
	schedule->fibers[0]->fiber = ConvertThreadToFiberEx(0, FIBER_FLAG_FLOAT_SWITCH);
	UT_CHECK_TRUE (schedule->fibers[0]->fiber != 0);
#endif
#ifdef UT_PLATFORM_LINUX
	UT_CHECK_TRUE(0 == getcontext(&schedule->fibers[0]->fiber));
#endif

	schedule->fibers[0]->schedule = schedule;
	schedule->fibers[0]->ud = 0;
	schedule->fibers[0]->ufunc = 0;
	schedule->fibers[0]->index = 0;
	schedule->fibers[0]->state = FIBER_RUNNING;

	return schedule;

FAIL:
	ut_fiber_schedule_close(schedule);
	
	return 0;
}

static int32_t ut_get_fiber_freeslot(ut_fiber_schedule_t* schedule)
{
	int32_t free_slot = -1;
	int32_t i = 0;
	for (i=0; i<schedule->cap; i++)
	{
		if (schedule->fibers[i] == 0)
		{
			free_slot = i;
			break;
		}
	}
	if (free_slot < 0)
	{
		struct ut_fiber** fibers = UT_NEW_ARRAY(struct ut_fiber*, schedule->cap*2);
		if (fibers == 0)
		{
			return -1;
		}
		memcpy(fibers, schedule->fibers, sizeof(struct ut_fiber*)*schedule->cap);
		free_slot = schedule->cap;
		schedule->cap *= 2;
		UT_DELETE(schedule->fibers);
		schedule->fibers = fibers;
	}

	return free_slot;
}

#ifdef UT_PLATFORM_WINDOWS
ut_fiber_t*	ut_fiber_create(ut_fiber_schedule_t* schedule, fiber_func func, int32_t stacksize, void* ud)
{
	int32_t free_slot = ut_get_fiber_freeslot(schedule);
	UT_ASSERT_RV (free_slot > 0, 0);

	schedule->fibers[free_slot] = UT_NEW(struct ut_fiber);
	if (schedule->fibers[free_slot] == 0)
	{
		return 0;
	}

	schedule->fibers[free_slot]->schedule = schedule;
	schedule->fibers[free_slot]->ud = ud;
	schedule->fibers[free_slot]->ufunc = func;
	schedule->fibers[free_slot]->index = free_slot;
	schedule->fibers[free_slot]->state = FIBER_SUSPEND;
	schedule->fibers[free_slot]->fiber = CreateFiberEx(4096, stacksize, FIBER_FLAG_FLOAT_SWITCH, fiberStartRoutine, schedule->fibers[free_slot]);

	if (schedule->fibers[free_slot]->fiber == 0)
	{
		UT_DELETE(schedule->fibers[free_slot]);
		return 0;
	}

	return schedule->fibers[free_slot];
}
#endif

#ifdef UT_PLATFORM_LINUX
ut_fiber_t*	ut_fiber_create(ut_fiber_schedule_t* schedule, fiber_func func, int32_t stacksize, void* ud)
{
	ut_fiber_t* new_fiber = 0;
	uintptr_t fiber_ptr = 0;
	int32_t free_slot = ut_get_fiber_freeslot(schedule);
	UT_ASSERT_RV (free_slot > 0, 0);

	new_fiber = UT_NEW(struct ut_fiber);
	UT_CHECK_TRUE (0 != new_fiber);

	new_fiber->szstack = UT_NEW_ARRAY(char, stacksize);
	UT_CHECK_TRUE (0 != new_fiber->szstack);

	UT_CHECK_TRUE (0 == getcontext(&new_fiber->fiber));
	new_fiber->fiber.uc_stack.ss_sp = new_fiber->szstack;
	new_fiber->fiber.uc_stack.ss_size = stacksize;
	new_fiber->fiber.uc_link = &schedule->fibers[0]->fiber;

	fiber_ptr = (uintptr_t)new_fiber;
	makecontext(&new_fiber->fiber, (void (*)(void))fiberStartRoutine, 2, (uint32_t)fiber_ptr, (uint32_t)(fiber_ptr>>32));

	new_fiber->schedule = schedule;
	new_fiber->ud = ud;
	new_fiber->ufunc = func;
	new_fiber->index = free_slot;
	new_fiber->state = FIBER_SUSPEND;

	schedule->fibers[free_slot] = new_fiber;
	return new_fiber;

FAIL:
	if (new_fiber != 0)
	{
		if (new_fiber->szstack != 0)
		{
			UT_DELETE(new_fiber->szstack);
		}
		UT_DELETE(new_fiber);
	}

	return 0;
}
#endif

void	ut_fiber_delete(ut_fiber_schedule_t* schedule, ut_fiber_t* fiber)
{
	UT_ASSERT_R(fiber->index<schedule->cap && schedule->fibers[fiber->index] == fiber);
	UT_ASSERT_R(fiber->index != 0);

	schedule->fibers[fiber->index] = 0;
#ifdef UT_PLATFORM_WINDOWS
	if (fiber->fiber != 0)
	{
		DeleteFiber(fiber->fiber);
	}
#endif
#ifdef UT_PLATFORM_LINUX
	UT_DELETE(fiber->szstack);
#endif

	UT_DELETE(fiber);
}

ut_fiber_t*	ut_fiber_current(ut_fiber_schedule_t* schedule)
{
	return schedule->fibers[schedule->ncur];
}

int32_t		ut_fiber_state(ut_fiber_t* fiber)
{
	return fiber->state;
}