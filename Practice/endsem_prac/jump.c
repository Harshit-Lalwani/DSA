#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int t[n];
    t[0] = 0;
    for(int i=1;i<n;i++)
    {
        scanf("%d",&t[i]);
    }
    for(int  i =0;i<n;i++)
    {
        //printf("t[%d] = %d\n",i,t[i]);
    }
    int jumps = 0,index = n-1;
    while(t[index]!=0)
    {
        //printf("index = %d\t t[index] = %d\n",index,t[index]);
        index = t[index]-1;
        jumps++;
    } 
    
    printf("%d",jumps);
}