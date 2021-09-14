#include<stdio.h>
#include<string.h>

int main()
{
    int i, len;
    char String[50];
    char* read;
    read = String;
    printf("INPUT : ");
    scanf_s("%s", String);
    printf("OUTPUT : ");
    len = strlen(String);
    len -= 1;
    while (len != -1)
    {
        for (i = 0; i <= len;)
        {
            printf("%c", *read);
            read++;
            i++;
        }
        printf("\n         ");
        read -= i;
        len--;

    }

    return 0;
}