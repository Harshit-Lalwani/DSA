#include<stdio.h>
#include<stdlib.h>
#define MAX 5

typedef struct stack{
    int stack_arr[MAX];
    int top;
}stack;

void print_stack(stack* S)
{
    for(int i = 0;i<S->top;i++)
    {
        printf("%d ",S->stack_arr[i]);
    }
    printf("\n");
}

void push( int data,stack* S)
{
    if(S->top>=MAX-1)
    {
        printf("OVERFLOW!!\n");
        return;
    }
    else{
        (S->top)++;
        S->stack_arr[S->top]=data;
    }
}

void push( int data,stack* S)
{
    if(S->top==-1)
    {
        printf("Empty Stack\n");
        return;
    }
    else{
        (S->top)--;
        S->stack_arr[S->top]=0;
    }
}

int main()
{

}