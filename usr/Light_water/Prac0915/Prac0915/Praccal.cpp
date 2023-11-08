#include <stdio.h>
#pragma warning(disable:4996);

int calc(int i, int j);

int main()
{
	int num1, num2;

	printf("값을 입력하세요 : ");
	scanf("%d", &num1);

	printf("곱할 값: ");
	scanf("%d", &num2);

	printf("두 값의 곱은 %d 입니다. ", calc(num1, num2));
	
	return 0;
}

int calc(int i, int j)
{
	return i * j;
}
