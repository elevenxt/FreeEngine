/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#include "ut_packdata.h"

#include <memory.h>

enum
{
	intmask0 = 0x0000003F,
	intmask1 = 0x00001FC0,
	intmask2 = 0x000FE000,
	intmask3 = 0x07F00000,
	intmask4 = 0x78000000,
};

int32_t ut_pack_int(int32_t val, char* data, int32_t dl)
{
	//1为完整标志，1位符号标志 //6位数据0x0000003F	//7位数据0x00001FC0	//7位数据0x000FE000	//7位数据0x7F00000	//7位数据0x78000000
	int32_t bytes_num = 5;
	if (dl < 1)
	{
		return 0;
	}

	data[0] = 0;
	if (val < 0)
	{
		// 设置符号位
		data[0] |= 0x40;
		val = -val;
	}

	if ((val & intmask4) == 0)
	{
		bytes_num = 4;
		if ((val & intmask3) == 0)
		{
			bytes_num = 3;
			if ((val & intmask2) == 0)
			{
				bytes_num = 2;
				if ((val & intmask1) == 0)
				{
					bytes_num = 1;
				}
			}
		}
	}

	switch (bytes_num)
	{
	case 1:
		if (dl <1){return 0;}
		data[0] |= (val & intmask0);
		break;
	case 2:
		if (dl <2){return 0;}
		data[0] |= (val & intmask0);
		data[0] |= 0x80;
		data[1] = ((val & intmask1)>>6);
		break;
	case 3:
		if (dl <3){return 0;}
		data[0] |= 0x80;
		data[0] |= (val & intmask0);
		data[1] = ((val & intmask1)>>6);
		data[1] |= 0x80;
		data[2] = ((val & intmask2)>>13);
		break;
	case 4:
		if (dl <4){return 0;}
		data[0] |= 0x80;
		data[0] |= (val & intmask0);
		data[1] = ((val & intmask1)>>6);
		data[1] |= 0x80;
		data[2] = ((val & intmask2)>>13);
		data[2] |= 0x80;
		data[3] = ((val & intmask3)>>20);
		break;
	case 5:
		if (dl <5){return 0;}
		data[0] |= 0x80;
		data[0] |= (val & intmask0);
		data[1] = ((val & intmask1)>>6);
		data[1] |= 0x80;
		data[2] = ((val & intmask2)>>13);
		data[2] |= 0x80;
		data[3] = ((val & intmask3)>>20);
		data[3] |= 0x80;
		data[4] = ((val & intmask4)>>27);
		break;
	}

	return bytes_num;
}

int32_t ut_pack_data(const char* sz, int32_t szl, char* data, int32_t dl)
{
	int32_t nplen = ut_pack_int(szl, data, dl);
	if (nplen <= 0)
	{
		return 0;
	}

	if (nplen+szl>dl)
	{
		return 0;
	}

	memcpy(data+nplen, sz, szl);

	return nplen+szl;
}

int32_t ut_unpack_int(int32_t* val, char* data, int32_t dl)
{
	//1为完整标志，1位符号标志 //6位数据0x0000003F	//7位数据0x00001FC0	//7位数据0x000FE000	//7位数据0x7F00000	//7位数据0x78000000
	int32_t i = 0;
	(*val) = 0;
	for (i=0; i<5; i++)
	{
		if (dl < i)
		{
			return 0;
		}

		switch (i)
		{
		case 0:
			(*val) = data[i] & 0x3f;
			break;
		case 1:
			(*val) |= (data[i] & 0x7f)<<6;
			break;
		case 2:
			(*val) |= (data[i] & 0x7f)<<13;
			break;
		case 3:
			(*val) |= (data[i] & 0x7f)<<20;
			break;
		case 4:
			(*val) |= (data[i] & 0x7f)<<27;
			break;
		}

		if ((data[i] & 0x80) == 0)
		{
			break;
		}
	}

	if (i >= 5)
	{
		return 0;
	}

	if (data[0] & 0x40)
	{
		(*val) = -(*val);
	}

	return i+1;
}

int32_t ut_unpack_data(char* sz, int32_t* szl, char* data, int32_t dl)
{
	int32_t datalen = 0;
	int32_t rlen = ut_unpack_int(&datalen, data, dl);
	if (rlen <= 0)
	{
		return 0;
	}

	if ((rlen + datalen) > dl || datalen > *szl)
	{
		return 0;
	}

	memcpy(sz, data+rlen, datalen);
	*szl = datalen;

	return rlen + datalen;
}