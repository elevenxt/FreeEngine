/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_LIST_H_
#define _UT_LIST_H_

#include "ut_def.h"

__C_BEGIN_DECLS

typedef struct ut_list
{
	void*	value;
	struct ut_list* head;
	struct ut_list* next;
	struct ut_list* prev;
}ut_list_t;

ut_err_code_t	ut_list_init(ut_list_t* list, void* value);
ut_err_code_t	ut_list_push_head(ut_list_t* head, ut_list_t* list);
ut_err_code_t	ut_list_push_tail(ut_list_t* head, ut_list_t* list);
ut_list_t*		ut_list_pop_head(ut_list_t* head);
ut_list_t*		ut_list_pop_tail(ut_list_t* head);
ut_err_code_t	ut_list_remove(ut_list_t* list);
ut_err_code_t	ut_list_isempty(ut_list_t* list);
void			ut_list_transform(ut_list_t* from, ut_list_t* to);

__C_END_DECLS

#endif