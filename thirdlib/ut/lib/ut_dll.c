/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include <stdio.h>
#ifdef WIN32			
#include <windows.h>
#endif 
#if unix
#include <dlfcn.h>
#endif 

#include "ut_dll.h"


/*----------------------------------------------------------*/
/*						Load DLL							*/
/*----------------------------------------------------------*/
dll_handle_t ut_dll_load(const char *dllname)
{
	dll_handle_t dllmod=0;

	if(dllname==0) 
	{
		return 0;
	}

#ifdef _WIN32
	dllmod = LoadLibrary(dllname);
#endif

#ifdef unix
	dllmod = dlopen(dllname, RTLD_LAZY);
#endif

	return dllmod;
}

/*----------------------------------------------------------*/
/*						Access DLL							*/
/*----------------------------------------------------------*/
void *ut_dll_access(dll_handle_t dllmod, const char *funcname)
{
	dll_func_handle_t dll_func=0;

	if(dllmod==0) 
	{
		return 0;
	}
	if(funcname==NULL) 
	{
		return NULL;
	}
#ifdef _WIN32
	dll_func = GetProcAddress((HMODULE)dllmod, funcname); 
#endif

#ifdef unix
	dll_func = dlsym(dllmod, funcname);
#endif

	return dll_func;
}

/*----------------------------------------------------------*/
/*						Close DLL							*/
/*----------------------------------------------------------*/
void ut_dll_close(dll_handle_t dllmod)
{
	if(dllmod==0)return;

#ifdef _WIN32
	FreeLibrary((HMODULE)dllmod);
#endif

#ifdef unix
	dlclose(dllmod);
#endif

	return;
}

