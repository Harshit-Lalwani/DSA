#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300000

int max(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    int ls[MAX_N] = {0};
    int count[MAX_N] = {0};

    int n;
    int largest_num=0; //largest number in ans subarray
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
        printf("1\n0\n");
        return 0;
    }

    int max_count = 0;
    // int smallest_in_longest = 0;

    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            ls[arr[i]] = arr[i];
            count[arr[i]] = 1;
            if(max_count<1)
            {
                max_count = 1;
                // smallest_in_longest = arr[i];
                largest_num = arr[i];
            }

            continue;
        }

        if(ls[arr[i]] != 0)
        {
            if(ls[arr[i]-1] != 0)
            {
                ls[arr[i]] = ls[arr[i]-1]; 
            }
        }
        else
        {
            if (ls[arr[i]-1] != 0)
            {
                ls[arr[i]] = ls[arr[i]-1];
                count[ls[arr[i]]] ++;
                if(count[ls[arr[i]]]>max_count)
                {
                    max_count = count[ls[arr[i]]];
                    // smallest_in_longest = ls[arr[i]];
                    largest_num = arr[i];
                }
            }
            else
            {
                ls[arr[i]] = arr[i];
                count[arr[i]] = 1;
                max_count = max(max_count,1);
                if(max_count<1)
                {
                    max_count = 1;
                    // smallest_in_longest = arr[i];
                    largest_num = arr[i];
                }
            }
        }
    }  

    int out[n];
    int prev_index  = n;
    int count_out = 0;
    int found = 0;

    while(ls[largest_num] != 0 && prev_index>=1) {
        found =0;
        for(int j = prev_index - 1; j >= 0; j--) {
            if(arr[j] == largest_num) {
                found =1;
                out[count_out++] = j;
                prev_index = j;
                break;
            }
        }

        if(found ==0)
        {
            break;
        }
        largest_num--;
    }

    printf("%d\n", count_out);

    for(int i = count_out-1; i>=0; i--) {
        printf("%d ", out[i]);
    }

    printf("\n");

    // free(arr);
    // free(out);

    return 0;
}