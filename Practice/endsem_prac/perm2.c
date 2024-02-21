#include<stdio.h>

void swap(int* x, int * y)
{
    int temp = *y;
    *y = *x;
    *x = temp;
}

void printarr(int* a, int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",*(a+i));
    }
    printf("\n");
}


void permute(int* a, int start, int len)
{
    if(start == len-1)
    {
        printarr(a,len);
    }
    else{
        //printf("start = %d,len = %d\n",start,len);
        for(int i =start;i<len;i++)
        {
            swap(a+start,a+i);
            //printf("starting permute:\n");
            permute(a,start+1,len);
            swap(a+start,a+i);
        }
    }
}

int main()
{
    int a[] = {1,2,3,4};
    permute(a,0,4);
}