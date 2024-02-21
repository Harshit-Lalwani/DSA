#include<stdio.h>


int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int a[n], req[31] = {0};
    for(int i =0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<31;i++)
    {////printf("\nChecking digit %d  ",i);
        for(int j=0;j<n;j++)
        {
            ////printf("a[%d] = %d, unit digit  = %d   ",j,a[j],a[j]&1);
            if((a[j]&1) ==0)
            {
                req[i]++;
                ////printf("req[%d] = %d",i,req[i]);
            }
            a[j] = a[j]>>1;   
        }
    }
    

    // for(int i = 0;i<31;i++)
    // {
    //     //printf("\nreq[%d] = %d",i,req[i]);
    // }
    int index = 30;
    while(k>0 && index>=0)
    {
        //printf("\nreq[%d] = %d\tk=%d\n",index,req[index],k);
        if(req[index]>k)
        {
            //printf("req[index]>k");
            index--;
            continue;
        }
        else
        {
            //printf("\nreq[index]<=k");
            k-=req[index];
            req[index] =0;
            index--;
        }
    }
    int res = 0,temp =1;;

    for(int i = 0;i<31;i++)
    {
        if(req[i]==0)
        {
            res+=temp;
        }
        temp*=2;
    }

    printf("%d\n",res);

    //printf("\n");
}