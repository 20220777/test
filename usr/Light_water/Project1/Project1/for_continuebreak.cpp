#include<stdio.h>

int main(void)
{
	for (int i = 0; i < 10; ++i)
	{
		//i가 4보다 크면 for 문을 그만 나오너라.
		if (i > 4) break;

		printf("%d ", i);
	}
	return 0;
}