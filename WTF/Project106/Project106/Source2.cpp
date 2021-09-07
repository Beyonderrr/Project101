#include<stdio.h>

int main()
{
    int data[20], * Count;
    float Average = 0;
    printf("Enter data : ");
    for (int i = 0; i <= 9; i++)
    {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i <= 9; i++)
    {
        printf("%d ", data[i]);
    }
    Count = data;
    for (int i = 0; i <= 9; i++)
    {
        Average += Count[i];

    }

    Average /= 10;
    printf("\nAverage is : %f", Average);

    return 0;
}