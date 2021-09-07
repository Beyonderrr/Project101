#include<stdio.h>

int main()
{
    int data[10];
    float Average = 0;
    printf("Enter data : ");
    for (int i = 0; i <= 9; i++)
    {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i <= 9; i++)
    {
        Average += data[i];
        printf("%d ", data[i]);
    }
    Average /= 10;
    printf("\nAverage is : %f", Average);

    return 0;
}