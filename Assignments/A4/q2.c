/*
LOGIC: Make two heaps. One for caves with positive change. (min heap based on min oxygen required). Other for caves with negative change. (min heap based on oxygen required). Now pop from heap of positive caves and if current oxygen is greater than min oxygen required, then increase current oxygen, else return 0. Now, pop from the second heap, if current oxygen is greater than min oxygen required, then change current oxygen, else return 0. loop till heaps are empty. If final oxygen is greater than 0, return 1, else return 0.

NOTE: This can be optimized by breaking the loop as soon as current oxygen becomes less than 0.

CONSTRAINTS:
1 <= n <= 100
1 <= k <= 3e4
1 <= x[i] <= 3e4
-300 <= y[i] <= 300
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct cave{
    int oxygen_req;
    int change;
}cave;

cave* create_cave(int oxygen_req, int change)
{
    cave* c = (cave*)malloc(sizeof(cave));
    c->oxygen_req = oxygen_req;
    c->change = change;
    return c;
}

typedef struct heap{
    int size;
    int capacity;
    cave* arr;
}heap;

void swap(cave* a, cave* b)
{
    cave temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) { return (i-1)/2; }
int leftChild(int i) { return (2*i + 1); }
int rightChild(int i) { return (2*i + 2); }

heap* create_heap(int capacity)
{
    heap* h = (heap*)malloc(sizeof(heap));
    h->arr = (cave*)malloc(capacity * sizeof(cave));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heapify_root(heap* h, int i)
{
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < h->size && h->arr[left].oxygen_req < h->arr[smallest].oxygen_req)
        smallest = left;

    if (right < h->size && h->arr[right].oxygen_req < h->arr[smallest].oxygen_req)
        smallest = right;

    if (smallest != i) {
        swap(&h->arr[i], &h->arr[smallest]);
        heapify_root(h, smallest);
    }
}

void heapify_leaf(heap* h, int i)
{
    while (i != 0 && h->arr[parent(i)].oxygen_req > h->arr[i].oxygen_req) {
        swap(&h->arr[i], &h->arr[parent(i)]);
        i = parent(i);
    }
}

void insert(heap* h, cave c)
{
    if (h->size == h->capacity) {
        printf("\nOverflow: Could not insert\n");
        return;
    }

    h->size++;
    int i = h->size - 1;
    h->arr[i] = c;

    heapify_leaf(h, i);
}

cave extract_min(heap* h)
{
    if (h->size <= 0)
        return (cave){-1, -1};
    if (h->size == 1) {
        h->size--;
        return h->arr[0];
    }

    cave root = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    heapify_root(h, 0);

    return root;
}

void print_heap(heap* h)
{
    for (int i = 0; i < h->size; i++)
    {
        printf("req= %d\tchange = %d\n", h->arr[i].oxygen_req, h->arr[i].change);
    }
    printf("\n");
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);

    heap* p_heap = create_heap(n);
    heap* n_heap = create_heap(n);
    cave temp;
    int oxygen_req[n];
    int change[n];

    for(int i =0; i < n; i++)
    {
        // fflush(stdin);
        scanf("%d",&oxygen_req[i]);
        // fflush(stdin);
        // printf("oxygen_req = %d\n",oxygen_req[i]);
        // fflush(stdout);
    }    

    // fflush(stdin);
    // fflush(stdout);

    for(int i =0; i < n; i++)
    {
        // fflush(stdin);
        scanf("%d",&change[i]);
        // fflush(stdin);
        // printf("change = %d\n",change[i]);
        // fflush(stdout);
    }

    

    for(int i =0; i < n; i++)
    {
        // printf("oxygen_req = %d\tchange = %d\n",oxygen_req[i],change[i]);        
    }

    
    for(int i = 0; i < n; i++)
    {
        temp = *create_cave(oxygen_req[i], change[i]);
        if(change[i] > 0)
        {
            insert(p_heap, temp);
        }
        else
        {
            insert(n_heap, temp);
        }                
    }
    int p_size  = p_heap->size;
    int n_size = n_heap->size;

    // printf("positive heap: \n");
    // print_heap(p_heap);
    // printf("negative heap: \n");
    // print_heap(n_heap);

    // first, we iterate throught the positive change caves
    for (int i = 0; i < p_size; i++)
    {
        temp = extract_min(p_heap);
        if (temp.oxygen_req <= k)
        {
            k += temp.change;
        }
        else
        {
            printf("NO\n");
            return 0;
        }
    }


    // then, we iterate through the negative change caves
    for (int i = 0; i < n_size; i++)
    {
        temp = extract_min(n_heap);
        // printf("oxygen_req = %d, k = %d\n",temp.oxygen_req, k);
        if (temp.oxygen_req <= k && k + temp.change >= 0)
        {
            k += temp.change;
        }
        else
        {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");

    free(p_heap->arr);
    free(p_heap);
    free(n_heap->arr);
    free(n_heap);
    return 0;
}