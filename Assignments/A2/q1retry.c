#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int l=0;  //l is the length of tree array

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

// typedef struct node
// {
//     struct node *parent;
//     struct node *left;
//     struct node *right;
//     bool colored;
// }node;

// typedef struct node* Tree;



//Create a tree array from the given array
int* treemaker(int n, int* arr)
{
    int i=1,j=1;
    int* tree = (int*)malloc(n*sizeof(int));
    tree[0] = arr[0];

    while(i<n)
    {
        if(j >= n) {
            n *= 2;
            tree = (int*)realloc(tree, n * sizeof(int));
            if(tree == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }
        }
        if(tree[j]==-1)
        {
            j++;
            continue;
        }

        if(arr[i]==1)
        {
            tree[j]=arr[i];
        }
        else{
            tree[j]=-1;
            if(2*j+1 < n) {
                tree[2*j+1]=-1;
            }
            if(2*j+2 < n) {
                tree[2*j+2]=-1;
            }
        }

        i++;
        j++;

    }

    l=j;
    return tree;
}

int leftchildindex(int i)
{
    return 2*i+1;
}

int rightchildindex(int i)
{
    return 2*i+2;
}

int parentindex(int i)
{
    return (i-1)/2;
}

int main()
{
    int n =9;
    int arr[] = {1,0,1,0,1,1,0,0,1};

    int* tree = treemaker(n, arr);

    for(int i=0; i<l; i++)
    {
        printf("%d ", tree[i]);
    }
    printf("\n");
}