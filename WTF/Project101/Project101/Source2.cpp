#include<stdio.h>
int main()
{
    int Scale, Devide = 2, Judment = 0, Dothing = 2;
    printf("Enter a number : ");
    scanf("%d", &Scale);

    while (Dothing < Scale)
    {
        while (Devide < Dothing)
        {
            if (Dothing % Devide == 0)
            {
                Judment++;
            }
            Devide++;
        }
        if (Judment == 0)
        {
            printf("%d ", Dothing);
        }
      
        Judment = 0;
        Devide = 2;
        Dothing++;
    }
    return 0;
}