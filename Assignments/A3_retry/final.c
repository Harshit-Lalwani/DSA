#include<stdio.h>
#include<stdlib.h>

#define MAX 100019

typedef struct Node
{
    int value;
    int index;
    int len;
    struct Node* next;
    struct Node* prev_in_subarr;
}Node;

//hashtable has an array of nodes, ech index represents a modular class
typedef struct HashTable
{
    int size;
    Node* table[MAX];
    int maxlen;
    Node* last;
}HashTable;

int hash(int value)
{
    return value%MAX;
}

HashTable* init()
{
    HashTable* h = (HashTable*)malloc(sizeof(HashTable));
    h->size = 0;
    for(int i=0; i<MAX; i++)
    {
        h->table[i] = NULL;
    }
    h->maxlen = 1;
    h->last = NULL;
    
    return h;
}

// this function will insert a new node at the end of the linked list corresponding to its hash value

void insert_to_ll(int value, int index, HashTable* h)
{
    int key = hash(value);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->index = index;
    new_node->next = NULL;
    new_node->prev_in_subarr = NULL;
    new_node->len = 1;

    if(h->table[key] == NULL)
    {
        h->table[key] = new_node;
    }
    else
    {
        Node* temp = h->table[key];
        //if first node of this list has the same value as the new node, then i update the first node with new index rather than inserting a new node

        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        if(temp->value == value && temp->index == index-1)
        {
            temp->index++;
        }
        else{
            temp->next = new_node;
        }
    }

    // If this is the first node being inserted, set it as the last node of the hashtable
    if (h->size == 0)
    {
        h->last = new_node;
    }

    h->size++;  // Increase the size of the hashtable

    int l = hash(value-1);
    Node* longest_prev=NULL;
    if(h->table[l] != NULL)
    {
        Node* temp = h->table[l];
        
        while(temp != NULL)
        {
            if(temp->value == value-1 && temp->index < index)
            {
                if(longest_prev == NULL)
                {
                    longest_prev = temp;
                }
                else if(temp->len > longest_prev->len)
                {
                    longest_prev = temp;
                }
                // new_node->prev_in_subarr = temp;
                new_node->len = temp->len + 1;
                              
            }
            temp = temp->next;
        }    
        
    }
    if(longest_prev!=NULL)
    {
        new_node->prev_in_subarr = longest_prev;
        new_node->len = longest_prev->len + 1;
    }
    // new_node->prev_in_subarr = longest_prev;
    
    if(new_node->len > h->maxlen)
    {
        h->maxlen = new_node->len;
        h->last = new_node;
        // printf("maxlen: %d\n", h->maxlen);
    }  

    // printf("value: %d, index: %d, len: %d\n", new_node->value, new_node->index, new_node->len);
    
    // if(new_node->prev_in_subarr != NULL)
    // {
    //     printf("for prev_in_subarr: value: %d, index: %d, len: %d\n", new_node->prev_in_subarr->value, new_node->prev_in_subarr->index, new_node->prev_in_subarr->len);
    // }
}


void print_hashtable(HashTable* h)
{
    printf("size = %d, maxlen = %d\n", h->size, h->maxlen);
    // for(int i=0;i<MAX;i++)
    // {
    //     if(h->table[i] != NULL)
    //     {
    //         Node* temp = h->table[i];
    //         while(temp != NULL)
    //         {
    //             printf("%d ", temp->value);
    //             temp = temp->next;
    //         }
    //         printf("\n");
    //     }
    // }
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i =0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    HashTable* h = init();

    for(int i=0;i<n;i++)
    {
        // printf("i = %d\n------------------------------------\n", i);
        // print_hashtable(h);
        insert_to_ll(arr[i], i, h);
    }

    printf("%d\n", h->maxlen);
    int out[h->maxlen];
    Node* temp = h->last;
    while(temp != NULL)
    {
        out[temp->len-1] = temp->index;
        temp = temp->prev_in_subarr;
    }

    for(int i=0;i<h->maxlen;i++)
    {
        printf("%d ", out[i]);
    }
    printf("\n");
    return 0;
}
