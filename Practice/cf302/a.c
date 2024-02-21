#include<stdio.h>

int main()
{
    int x,y;

    scanf("%d",&x);
    scanf("%d",&y);

    if(x>y)
    {
        printf("%d %d\n",y, x/2-y/2);
    }
    else
    {
        printf("%d %d\n",x,y/2-x/2);

    }
}