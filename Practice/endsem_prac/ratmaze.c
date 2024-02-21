#include<stdio.h>
//i,j = position; r,c = dimensions
// 0 =both invalid
// 1= both valid
// 2 = right
// 3 = down
// 4 = reached final
int check(int m[5][5], int i, int j, int r,int c)
{   int right=1,down =1;
    
    if(i == r-1 && j == c-1)
    {
        return 4;
    }

    if(i==r-1)
    {
        down =0;
    }
    else if(m[i+1][j])
    {
        down = 0;
    }

    if(j==c-1)
    {
        right =0;
    }
    else if(m[i][j+1])
    {
        right = 0;
    }

    if(right*down)
    return 1;

    else if(!(right+down))
    return 0;

    else if(right* (!down))
    return 2;
    
    else if((!right)*down)
    return 3;    
}



int main()
{
    int r =5,c=5;
    int m[5][5]={
        {0,0,0,0,0},
        {1,0,1,1,1},
        {0,0,0,0,0},
        {1,0,1,0,1},
        {1,1,1,0,0}
    };

    //printf("%d\n",check(m,4,4,r,c));

    
}