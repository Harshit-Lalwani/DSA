#include <stdio.h>
#include <stdlib.h>

#define alpha 10

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    Node* node;
    struct Queue* next;
} Queue;

Queue* newQueue(Node* node)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->node = node;
    q->next = NULL;
    return q;
}

Node* newNode(int data) {

    if(data == 0){
        return NULL;
    }
    else{
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
}

void enqueue(Queue* q, Node* node)
{
    if(q==NULL)
    {
        q = (Queue*)malloc(sizeof(Queue));
        q->node = node;
        q->next = NULL;
    }
    else
    {
        Queue* temp = q;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = (Queue*)malloc(sizeof(Queue));
        temp->next->node = node;
        temp->next->next = NULL;
    }
}

void dequeue(Queue* q)
{
    if(q==NULL)
    {
        return;
    }
    else
    {
        Queue* temp = q;
        while(temp->next != NULL && temp->next->next != NULL)
        {
            temp = temp->next;
        }

        if(temp->next != NULL) {
            free(temp->next);
            temp->next = NULL;
        }
    }
}

Node* buildTree(int* levelOrder, int n) {


    int i=0; //i iterates over array levelOrder
    Node* root = newNode(levelOrder[0]);
    Queue* q1 = newQueue(root);
    Queue* q2 = NULL;
    Node* temp;
    Node* child;
    Queue* next;
    int x;


    while(i<n)
    {
       i++;

        //q1 contains current level
         while(q1!=NULL && i<n)
        {
            temp = q1->node;
            dequeue(q1);

            if(i<n) {
                child = newNode(levelOrder[i]);
                temp->left  = child;
                i++;
                //store next level in q2
                if(child!=NULL)
                {
                    enqueue(q2, child);
                }
            }

            if(i<n) {
                child = newNode(levelOrder[i]);
                temp->right  = child;
                i++;
                //store next level in q2
                if(child!=NULL)
                {
                    enqueue(q2, child);
                }
            }
        }
        q1 = q2;
        //empty q2 so that q2=NULL

        while(q2!=NULL)
        {
            dequeue(q2);
        }
        //this part is not compulsory for small trees but it is good to empty q2
        q2= NULL;

    }

    return root;
}

void print2DUtil(Node* root, int len)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    len += alpha;

    // Process right child first
    print2DUtil(root->right, len);

    // Print current node after len
    // count
    printf("\n");

    for(int i = alpha; i < len ; i++)
    {
        printf(" ");
    }
    printf("%d\n", root->data);

    // Process left child
    print2DUtil(root->left, len);
}
// Wrapper over print2DUtil()
void print2D(Node* root)
{
    // Pass initial len count as 0
    print2DUtil(root, 0);
}



int main() {
    int levelOrder[] = {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1};
    int n = sizeof(levelOrder) / sizeof(levelOrder[0]);

    Node* root = buildTree(levelOrder, n);

    Node* root1 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left = newNode(4);

    // Now root points to the root of the constructed binary tree.
    // You can add code here to test the tree.

    print2D(root);


    return 0;
}