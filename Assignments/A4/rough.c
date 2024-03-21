#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);

    int change[n];
    int oxygen_req[n];
    

    // for(int i =0; i < n; i++)
    // {
    //     scanf("%d",&oxygen_req[i]);
    //     // printf("oxygen_req = %d\n",oxygen_req[i]);
    // }    
    // for(int i =0; i < n; i++)
    // {
    //     scanf("%d",&change[i]);
    //     // printf("oxygen_req = %d\n",oxygen_req[i]);
    // }  
    for(int i=0;i<n;i++) scanf("%d",&oxygen_req[i]);
    for(int i=0;i<n;i++) scanf("%d",&change[i]); 

    for(int i = 0; i < n; i++)
    {
        printf("oxygen_req = %d\tchange = %d\n",oxygen_req[i],change[i]);        
    }

    int temp1;
    int temp2;

    scanf("%d")

    
}

/*
input format 1:
n k
oxygen_req[0] oxygen_req[1] ... oxygen_req[n-1]
change[0] change[1] ... change[n-1]

input format 2:
n
k
oxygen_req[0]
oxygen_req[1]
...
oxygen_req[n-1]
change[0]
change[1]
...
change[n-1]

input format 3:
n k oxygen_req[0] oxygen_req[1] ... oxygen_req[n-1] change[0] change[1] ... change[n-1]
*/