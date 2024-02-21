//read problem here: https://www.spoj.com/problems/SOLVEIT/
#include<stdio.h>
#include<stdlib.h>


int main()
{
    int n,q,k,x;
    scanf("%d %d",&n,&q);

    int* arr = (int*)calloc(n, sizeof(int));

    for(int i=0;i<q;i++)
    {
        scanf("%d %d",&x,&k);
        if(x==1)
        {
            arr[k]=-1;
        }

        else{
            
        }
    }


}