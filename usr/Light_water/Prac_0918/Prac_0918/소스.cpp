#include <stdio.h>

int main()
{
	for (int i = 1; i <= 9; i++)  //i 1부터 9까지 1씩 증가
	{
		for (int j = 1; j <= 9; j++)  //j 1부터 9까지 1씩 증가
		{
			printf("%d * %d = %d\n", i, j, i * j);

		}
		printf("-------------------\n");

	}
}
