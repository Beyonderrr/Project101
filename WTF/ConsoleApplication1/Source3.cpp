#include<stdio.h>
int main()
{   /*TODO: ��¹������Ѻ����Ţ 1 ��������������������Ҵ�ٻ����ͧ����*
    ����������������մ�ҹ��ҡѺ��Ƿ���Ѻ����Ҵѧ������ҧ*/
    int x, y, i;
    scanf("%d", &x);
    for (y = 0; y < x; y++)
    {
        for (i = 0; i < x; i++)
        {
            printf("*");
        }
        printf("\n");
    }


    return 0;
}