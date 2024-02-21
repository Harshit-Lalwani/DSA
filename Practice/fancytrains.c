/*Problem Description
There are n stations numbered 1, 2, ...n . Stations i and j are connected via a
train (1 i, j n) iff li — jl S 2. The price of such a train would be lai
ajl where ai is an input array denoting the ratings of stations. If you travel
optimally, find the minimum cost to travel form station 1 to station n .
Input Format
The first line of input contains a single integer n denoting the number of
stations.
The second line contains n space-seperated integers, ai .
Input constraints
• 2 < n < 105
< 104
Output Format
Print one integer, the minimum cost to travel from station 1 to station n .*/

#include<stdio.h>

int max(int x, int y)
{
    if(x>y)
    return x;

    else
    return y;
}
int diff(int* a, int x, int y)
{
    int t  = *(a+x) - *(a+y);
    return max(t, -1*t);
}

int min(int x, int y)
{
    return x+y-max(x,y);
}

int optimal(int n, int* a)
{
    if(n==1)
    {
        return 0;       //case of single station
    }
    else if(n<=3)
    {
        return diff(a,0,n-1); //case when first and last station are connected
    }
    else{
        return min((diff(a,0,1)+optimal(n-1,a+1)), diff(a,0,2)+optimal(n-2,a+2));
    }
}


int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("Ans: %d\n",optimal(n,a));
}