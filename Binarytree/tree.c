#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}node;

void pre_order(node* T)
{
    if(T!=NULL)
    {
        printf("%d, ",T->data);
        pre_order(T->left);
        pre_order(T->right);
    }
}

void post_order(node* T)
{
    if(T!=NULL)
    {

        post_order(T->left);
        post_order(T->right);
        printf("%d, ",T->data);
    }
}

void current_order(node* T)
{
    if(T!=NULL)
    {
        pre_order(T->left);
        printf("%d, ",T->data);
        pre_order(T->right);
    }
}

int main()
{
    node *root;
    root=(node*)malloc(sizeof(node));
    root->data=1;
    root->left=(node*)malloc(sizeof(node));
    root->right=(node*)malloc(sizeof(node));
    root->left->data=2;
    root->right->data=3;
    root->left->left=(node*)malloc(sizeof(node));
    root->left->right=(node*)malloc(sizeof(node));
    root->left->left->data=4;
    root->left->right->data=5;
    root->right->left=(node*)malloc(sizeof(node));
    root->right->right=(node*)malloc(sizeof(node));
    root->right->left->data=6;
    root->right->right->data=7;
    pre_order(root);
    printf("\n");
    post_order(root);
    printf("\n");
    current_order(root);
    printf("\n");
}