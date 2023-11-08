#include <stdio.h>
int main(void)
{
	//for continue
	printf("for continue ex.\n");
	for (int i = 0; i < 10; ++i)
	{
		// i를 2로 나누었을 때 나머지가 0이면 continue를 타라
		if (i % 2 == 1) continue;
		
		printf("%d ", i);
	}
	printf("\n");

	return 0;
}