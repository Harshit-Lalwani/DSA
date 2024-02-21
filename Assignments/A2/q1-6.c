#include <stdio.h>
#include <stdlib.h>

int glo =0;

2D print function for trees, comment while submitting on OJ

#define alpha 10
// void print2DUtil(Node* root, int len)
// {
//     // Base case
//     if (root == NULL)
//         return;
//     // Increase distance between levels
//     len += alpha;
//     // Process right child first
//     print2DUtil(root->right, len);
//     // Print current node after len
//     // count
//     printf("\n");
//     for(int i = alpha; i < len ; i++)
//     {
//         printf(" ");
//     }
//     printf("%d\n", root->data);
//     // Process left child
//     print2DUtil(root->left, len);
// }
// // Wrapper over print2DUtil()
// void print2D(Node* root)
// {
//     // Pass initial len count as 0
//     print2DUtil(root, 0);
// }

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


typedef enum{
    nophone,
    hasphone,
    sharedphone
} phone;

phone findmsubtree(Node* root)
{

    if(root==NULL)
    {
        return sharedphone;  //NULL nodes are assigned shared phone so that they cant share it with other but dont require extra phones as well
    }
    printf("running for %d\n",root->data);
    phone leftcheck  = findmsubtree(root->left);
    phone rightcheck = findmsubtree(root->right);

    //if either child lacks phone, give phone to parent
    if(leftcheck == nophone || rightcheck == nophone)
    {
        printf("Atleast one child of %d has no phone\n",root->data);
        printf("count increased\n");
        glo++;
        return hasphone;
    }

    //if either child has phone, parent gets shared phone
    else if(leftcheck == hasphone || rightcheck == hasphone)
    {
        printf("atleast one child of %d has phone and no child requires\n",root->data);
        return sharedphone;
    }

    //if both children have shared phones, parent should get shared phone from grandparent(if exists) or get phone itself(if it is root)
    else if(leftcheck == sharedphone && rightcheck == sharedphone){
         printf("Both children of %d have shared phones\n", root->data);
        return nophone;
    }
    else{
        printf("None\n");
    }
}


// int minimumCameras(Node* root, int* count)
//     {
//         if(root == NULL)
//             return 1;
//         int left = minimumCameras(root->left, count);
//         int right = minimumCameras(root->right, count);
//         if(left==-1 || right==-1)
//         {
//             *count++;
//             return 0;
//         }
//         if(left==0 || right==0)
//         {
//             return 1;
//         }
//         return -1;
//     }
// int minCameraCover(Node* root) {
//     int count = 0;
//     if(minimumCameras(root, count)==-1)
//     {

//     }

//     return count;
// }


int main()
{
    int m =0;
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Node* root = buildTree(arr, n);

    phone p  = findmsubtree(root);
    if(p== nophone)
    {
        glo++;
    }

    printf("%d\n",glo);


    // int ans = minCameraCover(root);
    // printf("%d\n",ans);
}

/*test case 1
9
1 2 0 3 0 4 0 0 5*/

/*test case 2
19
1 2 3 4 5 0 6 0 7 8 0 9 0 0 0 0 0 0 10*/
