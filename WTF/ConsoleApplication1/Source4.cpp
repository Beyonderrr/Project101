#include<stdio.h>
int main()
{   /*TODO: ��¹������Ѻ����Ţ 1 ��������������������Ҵ�ٻ����ͧ����*
    ����������������մ�ҹ��ҡѺ��Ƿ���Ѻ����Ҵѧ������ҧ*/
    int x, y, i;
    scanf("%d", &x);
    for (y = x; y > 0; y--)
    {
        for (i = x; i > 0; i--)
        {
            printf("*");
        }
        printf("\n");
    }


    return 0;
}