#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* unitNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}


