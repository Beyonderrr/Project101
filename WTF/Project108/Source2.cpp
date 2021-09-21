#include<stdio.h>

int main()
{
    int height;
    int passfloor = 1;

    printf("Enter number : ");
    scanf("%d", &height);

    int space1 = height - 1;
    int count = 1;
    int space2 = height - 1;

    while (passfloor <= height)
    {

        for (int i = 0; i < space1; i++)
        {
            printf(" ");
        }

        space1 -= 1;

        for (int i = 0; i < count; i++)
        {
            printf("*");
        }

        count += 2;

        for (int i = 0; i < space2; i++)
        {
            printf(" ");
        }

        space2 -= 1;

        printf("\n");

        passfloor++;
    }

    return 0;
}