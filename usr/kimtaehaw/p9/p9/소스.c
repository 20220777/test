#include <stdio.h>
#include <string.h>

int main()
{
    int i = 0;
    int a[1024] = {0};
    int* p = 0;

    p = a;

    for (i = 0; i < 1024; i++)
    {
        p[i] = i;
    }
    for (i = 0; i < 1024; i++)
    {
        printf("%d\n", p[i]);
    }

    printf("---------------------------------\n");

    //memset(p, 0, sizeof(int));
    for (i = 0; i < 1024; i++)
    {
        p[i] = 0;
    }


    for (i = 0; i < 1024; i++)
    {
        *(p + i) = i;
    }

    for (i = 0; i < 1024; i++)
    {
        printf("%d\n", *(p + i));
    }

    for (i = 0; i < 1024; i++)
    {
        *p = i;
        p++;
        *p++;
        *(p++);
        (*p)++;
    }


    return 0;

}