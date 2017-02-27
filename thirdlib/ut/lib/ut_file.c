/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/

#include <stdio.h>
#include <sys/stat.h>
#include "ut_file.h"

int64_t ut_file_modifytime(const char* fname)
{
	FILE* fp = 0;
	int fd = 0;
	struct stat fileStat;
	if (fname == 0) {
		return 0;
	}

	fp = fopen(fname, "r");
	if (fp == 0) {
		return 0;
	}

	fd = fileno(fp);
	fstat(fd, &fileStat);

	fclose(fp);

	return fileStat.st_mtime;
}
