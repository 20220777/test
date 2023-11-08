#include <stdio.h>
#include "util.h"

int32_t asc2hex(uint8_t* dst, const int8_t* src)
{
	uint8_t temp = 0x00;
	int32_t i = 0;

	while (src[i] != 0x00)
	{
		temp = 0x00;

		if ((src[i] >= 0x30) && (src[i] <= 0x39))
			temp = src[i] - '0';
		else if ((src[i] >= 0x41) && (src[i] <= 0x5A))
			temp = src[i] - 'A' + 10;
		else if ((src[i] >= 0x61) && (src[i] <= 0x7A))
			temp = src[i] - 'a' + 10;
		else
			temp = 0x00;

		(i & 1) ? (dst[i >> 1] ^= temp & 0x0F) : (dst[i >> 1] = 0, dst[i >> 1] = temp << 4);

		i++;
	}

	return ((i + 1) / 2);
}

void print_title(const int8_t* title)
{
	printf("================================================\n");
	printf("  %s\n", title);
	printf("================================================\n");
}

void print_hex(const int8_t* valName, const uint8_t* data, const int32_t dataLen)
{
	int32_t i = 0;

	printf("%s [%dbyte] :", valName, dataLen);
	for (i = 0; i < dataLen; i++)
	{
		if (!(i & 0x0F))
			printf("\n");
		printf(" %02X", data[i]);
	}
	printf("\n");
}

void print_result(const int8_t* func, int32_t ret)
{
	if (ret)
	{
		printf("================================================\n");
		printf("  %s Failure!\n", func);
		printf("================================================\n");

		exit(0);
	}
	else
	{
		printf("================================================\n");
		printf("  %s Success!\n", func);
		printf("================================================\n");
	}
}


void word2byte(uint8_t* dst, const uint32_t src, const int32_t srcLen)
{
	int32_t i = 0, shift = 0;
	for (i = 0; i < srcLen; i++)
	{
		shift = (srcLen - (i + 1)) * 8;
		dst[i] = (uint8_t)((src >> shift) & 0xff);
	}
}
// EOF
