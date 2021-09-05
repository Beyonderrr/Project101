#include<stdio.h>

long fac(int number);

long main()
{
    int x;
    long fin;
    printf("Enter Number : ");
    scanf_s("%d", &x);
    fin = fac(x);
    printf("Value of factorial is : ");
    printf("%d", fin);
    return 0;
}

long fac(int number)
{
    int i = 1, z = number;
    long result = 1;
    while (i <= z)
    {
        result *= i;
        i++;
    }
    return result;

}