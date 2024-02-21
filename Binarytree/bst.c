#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int x)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = x;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node* root, int y)
{
    int x = root->data;
    if(y>x)
    {
        if(root->right==NULL)
        {
            root->right = createNode(y);
        }
        else
        {
            insert(root->right, y);
        }
    }
    else
    {
        if(root->left==NULL)
        {
            root->left = createNode(y);
        }
        else
        {
            insert(root->left, y);
        }
    }
}

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

Node* BST(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);
    Node* root = createNode(arr[n/2]);
    for(int i=0; i<n; i++)
    {
        if(i != n/2)
            insert(root, arr[i]);
    }
    return root;
}