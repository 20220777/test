#include <stdio.h>
#include "Calc.h"
#pragma warning(disable:4996)

int main()
{
	int num1, num2;
	char log;

		printf("Enter first number: ");
		scanf(" %d", &num1);
		
		printf("Enter second number: ");
		scanf(" %d", &num2);

		printf("Which logculation do you want?(+, -, *, /):  \n");
		scanf(" %c", &log);

		if (log == '+')
		{
			printf("Results: %d", Add(num1, num2));
		}
		else if (log == '-')
		{
			printf("Results: %d", Min(num1, num2));
		}
		else if (log == '*')
		{
			printf("Results: %d", Tim(num1, num2));

		}
		else if (log == '/')
		{
			printf("Results: %d", Div(num1, num2));

		}
		else
		{
			printf("Wrong Answer.\n Try again");
		}
}