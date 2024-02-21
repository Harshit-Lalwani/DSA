#include<stdio.h>

int main()
{
    int a[5] = {0};
    for(int i = 0;i<5;i++)
    {
        a[i]++;
        a[i]+=1;
    }

    for(int i = 0;i<5;i++)
    {
        printf("%d\n",a[i]);
    }
}