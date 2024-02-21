#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int is_colored;
    struct Node* left;
    struct Node* right;
    struct Node* up;
} Node;

typedef struct Queue {
    Node* node;
    struct Queue* next;
} Queue;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left= NULL;
    node->right = NULL;
    node->up = NULL;
    node->is_colored = 0;
    return node;
}

void enqueue(Queue** q, Node* node) {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->node = node;
    newQueue->next = NULL;
    if (*q == NULL) {
        *q = newQueue;
    } else {
        Queue* temp = *q;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newQueue;
    }
}

Node* dequeue(Queue** q) {
    if (*q == NULL) {
        return NULL;
    }
    Queue* temp = *q;
    *q = (*q)->next;
    Node* node = temp->node;
    free(temp);
    return node;
}

Node* buildTree(int* levelOrder, int n) {
    if (n == 0 || levelOrder[0] == 0) {
        return NULL;
    }
    Node* root = newNode(levelOrder[0]);
    Queue* q = NULL;
    enqueue(&q, root);
    for (int i = 1; i < n; i++) {
        Node* parent = dequeue(&q);
        if (levelOrder[i] != 0) {
            parent->left = newNode(levelOrder[i]);
            parent->left->up = parent;
            enqueue(&q, parent->left);
        }
        if (++i < n && levelOrder[i] != 0) {
            parent->right = newNode(levelOrder[i]);
            parent->right->up = parent;
            enqueue(&q, parent->right);
        }
    }
    return root;
}

int hascoloredneighbour(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->is_colored == 1)
    {
        return 1;
    }
    if(root->left!=NULL && root->left->is_colored == 1)
    {
        return 1;
    }
    if(root->right!=NULL && root->right->is_colored == 1)
    {
        return 1;
    }
    if(root->up!=NULL && root->up->is_colored == 1)
    {
        return 1;
    }
}

Node* findleafwithnocloredparent(Node* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->left == NULL && root->right == NULL && root->up!=NULL && root->up->is_colored == 0)
    {
        return root;
    }
    Node* left = findleafwithnocloredparent(root->left);
    if(left != NULL)
    {
        return left;
    }
    Node* right = findleafwithnocloredparent(root->right);
    if(right != NULL)
    {
        return right;
    }
    return NULL;
}


int main()
{
    int ans =0;
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Node* root = buildTree(arr, n);

    Node* leaf = findleafwithnocloredparent(root);

    //Case of only one node
    if(leaf->up ==NULL)
    {
        ans = 1;
    }

    else
    {
        //this while loop iterates once per leaf node
        while(leaf!=NULL)
        {
            if(hascoloredneighbour(leaf->up))
            {
                leaf->is_colored = 1;
                ans++;
                printf("colored %d\n", leaf->data);

            }

            leaf= leaf->up;
            //if the node, its parent, or any of its children are colored, then we dont color it and move to node->up(if it exists)

            while(hascoloredneighbour(leaf) && leaf->up!=NULL)
            {
                leaf = leaf->up;
            }

            {
                leaf = leaf->up;
                printf("shifted to %d\n", leaf->data);
            }
            leaf->is_colored = 1;
            ans++;
            printf("colored %d\n", leaf->data);
            //this while loop iterates once per node to be colored
            while(leaf->up!=NULL && leaf->up->up!=NULL)
            {
                leaf = leaf->up->up;

                leaf->is_colored = 1;
                ans++;
                printf("colored %d\n", leaf->data);
            }

            leaf = findleafwithnocloredparent(root);
        }
    }

    printf("%d\n", ans);

    return 0;
}

