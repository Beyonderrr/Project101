//*TODO:1.รับค่า 2.หาค่าตั้งแต่ 1จนถึง x//
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
    int i = number;
    long result = 1;
    while (i > 0)
    {
        result *= i;
        i--;
    }
    return result;

}