include<stdio.h>

int sp;
int sum = 1;

int main()
{
    int height;
    printf("Enter number : ");
    scanf("%d", &height);

    int sp = height - 1;

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= sp; j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= sum; k++)
        {
            printf("*");
        }
        for (int l = 1; l <= sp; l++)
        {
            printf(" ");
        }
        sp -= 1;
        sum += 2;
        printf("\n");
    }



    return 0;
}