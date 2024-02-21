//lux if: f(i)>f(j) if j>i
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int h[n],a[n];

    for(int i =0;i<n;i++)
    {
        scanf("%d",&h[i]);
    }

    a[n-1] = h[n-1];
    
    for(int i =n-2;i>=0;i--)
    {
        if(h[i]>a[i+1])
        a[i] = h[i];
        
        else{
            a[i] = a[i+1];
        }
    }

    for(int i =0;i<n;i++)
    {
        
        int x = a[i]-h[i]+1;
        if(x==1)
        {
            x--;
        }
        printf("%d ",x);
    }


}