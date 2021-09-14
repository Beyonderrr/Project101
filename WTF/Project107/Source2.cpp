#include<stdio.h>

int main()
{
    int i = 0;
    char String[50];
    char* scan;
    scan = String;
    printf("INPUT : ");
    scanf_s("%s", String);
    printf("OUTPUT : ");
    while (String[0] != '\0')
    {
        if (*scan != '\0')
        {
            printf("%c", String[i]);
            i++;
            scan++;
        }
        else
        {
            printf("\n         ");
            String[i - 1] = '\0';
            printf("%c", String[i]);
            scan -= i;
            i = 0;
        }
    }



    return 0;
}