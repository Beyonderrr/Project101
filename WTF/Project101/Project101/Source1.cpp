#include<stdio.h>
int mainn()
{
    int x, i = 2, y = 0;
    printf("Enter a number : ");
    scanf("%d", &x);

    while (i < x)
    {
        if (x % i == 0)
        {
            y += i;
        }
        i++;
    }
    if (y>0)
    {
        printf("%d is not a prime number", x);
    }
    else
    {
        printf("%d is a prime number", x);
    }

    return 0;
}