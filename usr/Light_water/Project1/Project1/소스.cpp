#include <stdio.h>

int main()
{
	printf("1~100까지 홀수들의 합은 다음과 같다. ");

	int sum = 0;
	for (int i = 1; i <= 100; ++i)
	{
		if (i % 2 == 0) continue;

		sum += i;
	}
	printf("홀수들의 합 : %d\n", sum);

	printf("This displays %d, too\n", 99);
	printf("and also display this : %.3f", 3.14);
}