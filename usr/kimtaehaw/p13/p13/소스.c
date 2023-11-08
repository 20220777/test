#include <stdio.h>
#include <string.h>

int main()
{
	char a[52];
	char* p;

	p = a;

	p = &a[26];

	for (int i = 'A'; i <= 'Z'; i++, p++)
	{
		*p = i;
		printf("%c\n",*p);
	}
	
	printf("------------------------------------------------\n");

	
	
	for (int i = 'a'; i <= 'z'; i++,p++)
	{
		*p = i;
		printf("%c\n",*p);
	}

	printf("------------------------------------------------\n");

	for (int i = 0; i < 52; i++)
	{
		printf("%c\n",a[i]);
	}

	




}