//aim: find largest contiguous subarray with consecutive elements(multiple possible answers, each is valid). Print its sie and indices of its elements
//LOGIC: arrays ls and count of size n
//ls[i] stores the smallest element in the subarray ending at arr[i]
//count[i] stores the number of elements in the subarray ending at arr[i]
//if arr[i] is the first element of a subarray, then ls[i] = arr[i] and count[i] = 1
//if arr[i] is not the first element of a subarray, then ls[i] = ls[j] (s.t arr[i]-1 = arr[j]) and count[i]++

// constaraints: a<=n<=200000, 1<=arr[i]<=1000000000

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300000

//func to find first index of number in array between l and r(inclusive)
int find_first(int arr[], int l, int r, int num)
{
    //printf("\nSearching for first occurrence of %d between indices %d and %d\n", num, l, r);
    for(int i=l;i<=r;i++)
    {
        //printf("\ti = %d, arr[i] = %d, num = %d\n",i,arr[i],num);
        if(arr[i]==num)
        {
            //printf("\tFound at index %d\n", i);
            return i;
        }
    }
    //printf("\tNot found\n");
    return -1;
}

int find_last(int arr[], int l, int r, int num)
{
    //printf("\nSearching for last occurrence of %d between indices %d and %d\n", num, l, r);
    for(int i=r;i>=l;i--)
    {
        //printf("\ti = %d, arr[i] = %d, num = %d\n",i,arr[i],num);
        if(arr[i]==num)
        {
            //printf("\tFound at index %d\n", i);
            return i;
        }
    }
    //printf("\tNot found\n");
    return -1;
}

int main()
{
    int n;
    scanf("%d",&n);

    int arr[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    if(n==0)
    {
        return 0;
    }
    if(n==1)
    {
        //printf("1\n0\n");
        return 0;
    }

    //keeping size MAX_N so that array can be initialized with -1
    int ls[MAX_N] = {-1};
    int count[MAX_N] = {-1};

    ls[0] = 0;
    count[0] = 1;
    int max_count =1;

    int j,k, l=0, r=0;
    for(int i=1;i<n;i++)
    {
        //printf("i = %d, val = %d\n",i,arr[i]);
        //Search for last occurence of arr[i] in window [l,r], say =k
        
        //HANDLE OCCURENCE OF DUPLICATES ALL KINDS OF CASES

        j = find_last(arr,0,i-1,arr[i]-1);
        l = j+1;
        k = find_first(arr,l,r,arr[i]);        

        if(k==-1)
        {
            if(j==-1)
            {
                ls[i] = i;
                count[i] = 1;
                l = i;
            }
            else
            {
                l = j+1;
                ls[i] = ls[j];
                count[i] = count[j]+1;
                if(count[i]>max_count)
                {
                    max_count = count[i];
                }
            }
        }

        // I make sure ls of last occurence is non-trivial, for all others, make it -1
        // to do this, I pass on ls value to current occurence and make it -1 for last(before current) occurence

        else
        {
            // if(ls[k]==k) //if k is the first occurence of arr[k]
            // {
            //     ls[i] = i;
            //     count[i] = 1;
            // }

            // else
            // {
            //     ls[i] = ls[k];
            //     count[i] = count[k];
            // }
            
            ls[i] = -1;
            count[i] = -1;
            l = k;
            //all occurence except this have been made -1              
            
        }
        r = i;

        for(int r=0;r<=i;r++)
        {
            //printf("i = %d, val = %d, ls = %d, count = %d\n",r,arr[r],ls[r],count[r]);
        }
        //printf("l = %d, r = %d\n",l,r);
        //TO UPDATE l AND r
    }

    printf("%d\n",max_count);

    //print index and values stored in arr, ls, count
    for(int i=0;i<n;i++)
    {
        //printf("i = %d, val = %d, ls = %d, count = %d\n",i,arr[i],ls[i],count[i]);
    }

    int last_index = find_first(count,0,n-1,max_count);
    int first_ans =  ls[last_index];
    int prev_index =n;
    //printf("first_ans = %d, last index = %d\n",first_ans,last_index);

    //print all elements where ls[i] = prev_index
    for(int i=0;i<n;i++)
    {
        if(ls[i]==first_ans && arr[i]!=arr[prev_index])
        {
            //printf("arr[%d] =%d\n",i,arr[i]);
            printf("%d ",i);
            prev_index = i;
        }
        
    }  
    
}