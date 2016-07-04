/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/


#include "ut_list.h"


ut_err_code_t ut_list_init(ut_list_t* list, void* value)
{
	list->next = list;
	list->prev = list;
	list->head = list;
	list->value = value;

	return ut_success;
}

ut_err_code_t ut_list_push_head(ut_list_t* head, ut_list_t* list)
{
	ut_list_t* prev = head;
	ut_list_t* next = head->next;
	if (ut_ec_iserror(ut_list_isempty(list)))
	{
		return ut_error;
	}
	prev->next = list;
	list->prev = prev;

	next->prev = list;
	list->next = next;

	list->head = head;

	return ut_success;
}

ut_err_code_t ut_list_push_tail(ut_list_t* head, ut_list_t* list)
{
	ut_list_t* prev = head->prev;
	ut_list_t* next = head;
	if (ut_ec_iserror(ut_list_isempty(list)))
	{
		return ut_error;
	}
	prev->next = list;
	list->prev = prev;

	next->prev = list;
	list->next = next;

	list->head = head;

	return ut_success;
}

ut_list_t*		ut_list_pop_head(ut_list_t* head)
{
	ut_list_t* poplist = head->next;

	ut_list_t* prev = head;
	ut_list_t* next = head->next->next;

	if (ut_ec_issuccess(ut_list_isempty(head)))
	{
		return 0;
	}

	ut_list_init(poplist, poplist->value);
	prev->next = next;
	next->prev = prev;

	return poplist;
}

ut_list_t*		ut_list_pop_tail(ut_list_t* head)
{
	ut_list_t* poplist = head->prev;

	ut_list_t* prev = head->prev->prev;
	ut_list_t* next = head;

	if (ut_ec_issuccess(ut_list_isempty(head)))
	{
		return 0;
	}

	ut_list_init(poplist, poplist->value);
	prev->next = next;
	next->prev = prev;

	return poplist;
}

ut_err_code_t ut_list_remove(ut_list_t* list)
{
	ut_list_t* prev = list->prev;
	ut_list_t* next = list->next;
	if (ut_ec_issuccess(ut_list_isempty(list)))
	{
		return ut_error;
	}

	ut_list_init(list, list->value);
	prev->next = next;
	next->prev = prev;

	return ut_success;
}

ut_err_code_t ut_list_isempty(ut_list_t* list)
{
	return list->next == list?ut_success:ut_error;
}

void			ut_list_transform(ut_list_t* from, ut_list_t* to)
{
	ut_list_t* lst = 0;

	while ((lst = ut_list_pop_head(from)) != 0)
	{
		ut_list_push_tail(to, lst);
	}
}