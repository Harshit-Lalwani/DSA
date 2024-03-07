// AIM: for a given array, find the longest subsequence of consecutive increasing numbers. NOTE: A subsequence retains the order of the elements in the original array, but not necessarily the contiguity.

//Constraints: 1<=n<=10^5, 1<=arr[i]<=10^9
// LOGIC:
// Implement hashtable to store int size and an array of Sentinel nodes(all initialized to poison values) 
// Each sentinel node contains int final_value, int lowest_value, count, Node* first
// first is the pointer to the first node of the linkedlist that stores the subsequence.
// Each Node caontains int value, int index(index from orgiinal array) Node* next
// for each element in the array, check if it is the successor of the last element of a subsequence. If yes, then create a new node and add it to the linkedlist of the corresponding sentinel node. Otherwise, if element does not already exist in any of the subsequences, add it to the linkedlist of (size of table)th sentinel node and then incremkent the size of the table.
// Finally, find the sentinel node with the maximum count and print the linkedlist of indices that sentinel node.

//Note: There are multiple possible correct answers. The code must print only one of them

#include <stdio.h>
#include <stdlib.h>

#define MAX 300000

typedef struct Node
{
    int value;
    int index;
    struct Node* next;
}Node;

typedef struct Sentinel
{
    int final_value;
    int lowest_value;
    int count;
    Node* first;
}Sentinel;

typedef struct HashTable
{
    int size;
    Sentinel* table[MAX];
}HashTable;

void init(HashTable* h)
{
    h->size = 0;
    for(int i=0; i<MAX; i++)
    {
        h->table[i] = (Sentinel*)malloc(sizeof(Sentinel));
        if(h->table[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
        h->table[i]->final_value = -1;
        h->table[i]->lowest_value = -1;
        h->table[i]->count = 0;
        h->table[i]->first = NULL;
    }
}


// function to insert node at end of linkedlist corresponding to kth sentinel node
void insert_to_ll(int value, int index, int k, HashTable* h)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        printf("Error: Memory allocation failed for new_node\n");
        exit(1);
    }
    new_node->value = value;
    new_node->index = index;
    new_node->next = NULL;

    if(h->table[k]->first == NULL)
    {
        h->table[k]->first = new_node;
    }
    else
    {
        Node* temp = h->table[k]->first;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    // Update final_value and count of the Sentinel node
    if(h->table[k]->lowest_value == -1)
    {
        h->table[k]->lowest_value = value;
    }
    h->table[k]->final_value = value;
    h->table[k]->count++;
}

//To be use only for debugging
void print_table(HashTable* h)
{
    printf("Size of table: %d\n", h->size);
    if(h->size == 0)
    {
        printf("Table is empty\n");
        return;
    }
    for(int i=0; i<h->size; i++)
    {
        printf("Sentinel node %d: final_value = %d, lowest_value = %d, count = %d\n", i, h->table[i]->final_value, h->table[i]->lowest_value, h->table[i]->count);
        
        Node* temp = h->table[i]->first;
        while(temp != NULL)
        {
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

//to print expected answer
void print_answer(HashTable* h, int index_of_maxcount)
{
    Node* temp = h->table[index_of_maxcount]->first;
    printf("%d\n", h->table[index_of_maxcount]->count);
    while(temp != NULL)
    {
        printf("%d ", temp->index);
        temp = temp->next;
    }
    printf("\n");

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
    HashTable* h = (HashTable*)malloc(sizeof(HashTable));
    if(h == NULL)
    {
        printf("Error: Memory allocation failed for HashTable\n");
        return 1;
    }
    init(h);
    int index_of_maxcount = 0;

    //one element will only be inserted to one list
    int index_of_lowest_start = -1;
    int makenew = 1;
    int x;
    // int used =0;    
    for(int i=0;i<n;i++)
    {
        makenew = 1;
        index_of_lowest_start = -1;
        // printf("arr[%d]=%d \n--------------------------------------------------------------------------------\n", i,arr[i]);
        
        x = arr[i];
        for(int j=0;j<(h->size);j++)
        {
                       
            if(h->table[j]->final_value == x-1)
            {
                // printf("predecessor %d found in sentinel node %d\n",x-1, j);
                makenew = 0;          
                
                if(index_of_lowest_start == -1)
                {
                    index_of_lowest_start = j;
                }
                else if(h->table[j]->lowest_value < h->table[index_of_lowest_start]->lowest_value)
                {
                    index_of_lowest_start = j;
                }

                // printf("index_of_lowest_start = %d\n", index_of_lowest_start);
            }
            else if(h->table[j]->lowest_value <=x && h->table[j]->final_value >= x)
            {
                // printf("%d found in sentinel node %d\n",x, j);
                makenew = 0;
                continue;
            }
        }

        if(index_of_lowest_start!=-1)
        {
            insert_to_ll(x, i, index_of_lowest_start, h);
            if(h->table[index_of_lowest_start]->count > h->table[index_of_maxcount]->count)
            {
                index_of_maxcount = index_of_lowest_start;
            }

        }       

                
        if(makenew)
        {
            insert_to_ll(x, i, h->size, h);
            // if(h->table[h->size]->count == 0)
            // {
            //     index_of_maxcount = h->size;
            // }
            h->size++;
        }


        // print_table(h);
        // printf("make new = %d\n", makenew);
    }

    // print_table(h); 
    print_answer(h, index_of_maxcount);

    return 0;
}