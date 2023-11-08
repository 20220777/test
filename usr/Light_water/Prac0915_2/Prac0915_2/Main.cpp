#include <stdio.h>
#include "Cal.h";
#pragma warning(disable:4996);


int main()
{
	int num1, num2;

	printf("Enter the number: ");
	scanf("%d", &num1);

	printf("Enter the second number: ");
	scanf("%d", &num2);

	char CAL;
	int val = 0;
	printf("Which calculation do you want?\n");
	scanf("%c", &CAL);

	if (CAL == '+')
	{
		int va1 = add(num1, num2);

	}
	else if (CAL == '-')
	{
		int va1 = min(num1, num2);
	}
	else if (CAL == '*')
	{
		int va1 = time(num1, num2);
	}
	else if (CAL == '/')
	{
		int va1 = div(num1, num2);
	}


	printf("Results = %d", val);

	return 0;

}