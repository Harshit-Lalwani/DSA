#include"stdio.h"
#include "stdlib.h"

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

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}node;

typedef struct node* Tree;

Tree init(int x){
    Tree head = (Tree)malloc(sizeof(node));
    head->right = NULL;
    head->left = NULL;
    head->val = x;
    return head;
}

//A lvel order traversal is provied to 

void printTree(Tree root)
{
    if(root==NULL)
    {
        return;
    }
    printf("%d ",root->val);
    printTree(root->left);
    printTree(root->right);
}

//func to find height of tree
int height(Tree root)
{
    if(root->left == NULL && root->right == NULL)
    {
        return 0;
    }
    else
    {
        return 1+max(height(root->left),height(root->right));
    }
}

//func to find m
int findm(int height, Tree root)
{
    if(height == 0)
    {
        return 0;
    }
    else if(height == 1)
    {
        return 1;
    }
    else
    {
        if(height%2 == 0)
        {
            //find number of nodes at odd levels
            int odd = 1+findm(height-1,root->left)+findm(height-1,root->right);
            return odd;
        }
        else
        {
            //find number of nodes at even levels
            int even = 1+findm(height-1,root->left)+findm(height-1,root->right);
            return even;
        }
    }
}

int main()
{
    // int n;
    // scanf("%d",&n);
    // int arr[n];
    // for(int i=0;i<n;i++)
    // {
    //     scanf("%d",&arr[i]);
    // }
    int n=9;
    int arr[]={1,1,0,1,0,1,0,0,1};

    Tree root = createTree(arr,n);
    printf("root->val = %d\n",root->val);
    printf("root->left->val = %d\n",root->left->val);
    printf("root->right->val = %d\n",root->right->val);
    printf("root->left->left->val = %d\n",root->left->left->val);

    // int h = height(root);
    // int m = findm(h,root);

    // printf("%d\n",m);
}