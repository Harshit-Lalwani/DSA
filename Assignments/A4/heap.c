#include<stdio.h>
#include<stdlib.h>

#define MAX 200000


int leftChild(int n)
{
    return 1 +2*n;
}

int rightChild(int n)
{
    return 2 +2*n;
}

int parent(int n)
{
    return (n-1)/2;
}

typedef int T;

void swap(T* a, T* b)
{
    // printf("swapping %d and %d\n",*a,*b);
    T temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct heap{
    int size;
    int capacity;
    T* arr;
}heap;

heap* create_heap(int capacity)
{
    heap* h = (heap*)malloc(sizeof(heap));
    h->arr = (T *)malloc(capacity* sizeof(T));
    h->size =0;
    h->capacity = capacity;
    return h;
}

void print_heap(heap* h)
{
    printf("heap size = %d\n",h->size);
    for(int i=0; i<h->size;i++)
    {
        printf("%d ",h->arr[i]);
    }
    printf("\n");
}

void heapify_root(heap* h)
{
    int i =0;
    int size = h->size;
    /*if both children exist and current is lesser than both, break. If lesser than only left, swap with right, if lesser than only right, swap with left
    if only left child exists and is smaller than current swap, else break
    if no child exists, break */
    // int a = 20;
    while(1)
    {
        // printf("current = %d\t",h->arr[i]);        
        if(rightChild(i)<size)
        {           
            // printf("left = %d\tright = %d\n",h->arr[leftChild(i)],h->arr[rightChild(i)]); 
            if(h->arr[i] < h->arr[leftChild(i)])
            {
                if(h->arr[i] < h->arr[rightChild(i)])
                {
                    // printf("current is smaller than both\n");
                    break;
                }

                else
                {
                    // printf("right < current < left\n");
                    swap(&h->arr[i], &h->arr[rightChild(i)]);
                    i = rightChild(i);
                }
            }

            else if(h->arr[i] < h->arr[rightChild(i)])
            {
                // printf("left < current < right\n");
                swap(&h->arr[i], &h->arr[leftChild(i)]);
                i = leftChild(i);
            }

            else
            {
                if(h->arr[leftChild(i)] < h->arr[rightChild(i)])
                {
                    // printf("left < right < current\n");
                    swap(&h->arr[i], &h->arr[leftChild(i)]);
                    i = leftChild(i);
                }
                else
                {
                    // printf("right < left < current\n");
                    swap(&h->arr[i], &h->arr[rightChild(i)]);
                    i = rightChild(i);
                }
            }
        }

        else if(leftChild(i) < size )
        {
            // printf("left = %d\n",h->arr[leftChild(i)]);
            if(h->arr[i] > h->arr[leftChild(i)])
            {
                // printf("left < current\n");
                swap(&h->arr[i], &h->arr[leftChild(i)]);
                i = leftChild(i);
            }    
            else
            {
                // printf("current < left\n");
                break;
            }
        }

        else
        {
            // printf("no child exists\n");
            break;
        }

    }
    print_heap(h);
}

void heapify_leaf(heap *h)
{
    int i = (h->size)-1;

    while(i>0)
    {
        if(h->arr[i] < h->arr[parent(i)])
        {
            swap(&h->arr[i], &h->arr[parent(i)]);
            i = parent(i);
        }
        else{
            break;
        }
    }
    // // printf("after applying heapify_leaf\n");
    print_heap(h);
}

void insert(T new, heap* h)
{
    h->arr[h->size] = new;
    h->size++;
    heapify_leaf(h);
    print_heap(h);
}

void extract_min(heap* h)
{
    h->size--;
    // printf("min = %d\n",h->arr[0]);
    swap(&h->arr[0],&h->arr[h->size]);
    heapify_root(h);
}


int main()
{

    // heap* h = create_heap(MAX);
    // h->size = 0;
    // h->capacity = MAX;

    // insert(1,h);
    // insert(2,h);
    // insert(6,h);
    // insert(3,h);
    // insert(5,h);
    // insert(7,h);
    // insert(4,h);

    // // print_heap(h);

    // extract_min(h);
    // // print_heap(h);
    // extract_min(h);
    // // print_heap(h);
    

}