#include<stdio.h>
#include<stdlib.h>

//AIM: given n stations, which have depth di and take time ti to fuel. Each station can fuel p units of fuel, and that too only once. Find the minimum time to reach depth d, if the submarine can carry infinite fuel and has . If submarine cannot reach the depth, print -1 and the max depth it can reach.

//LOGIC: qsort y depth in array. Push to heap (min heap of time). Do this till reachable depth. now, pop from heap and increase reachable distance by p. If not possible, print -1 and max reachable depth.

/*
CONSTRAINTS:
1<=n<=2e5
1<=k,d,p<=1e9
1<=depth[i]<=d-1
1<=time[i]<=1e9
No two stations at same depth
Use one station at most once
*/

typedef struct station{
    long long int depth;
    long long int time;
}station;

typedef struct heap{
    long long int size;
    long long int capacity;
    station* arr;
}heap;

void swap(station* a, station* b)
{
    station temp = *a;
    *a = *b;
    *b = temp;
}

long long int parent(long long int i) { return (i-1)/2; }
long long int leftChild(long long int i) { return (2*i + 1); }
long long int rightChild(long long int i) { return (2*i + 2); }

heap* create_heap(long long int capacity)
{
    heap* h = (heap*)malloc(sizeof(heap));
    h->arr = (station*)malloc(capacity * sizeof(station));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heapify_root(heap* h, long long int i)
{
    long long int smallest = i;
    long long int left = leftChild(i);
    long long int right = rightChild(i);

    if (left < h->size && h->arr[left].time < h->arr[smallest].time)
        smallest = left;

    if (right < h->size && h->arr[right].time < h->arr[smallest].time)
        smallest = right;

    if (smallest != i) {
        swap(&h->arr[i], &h->arr[smallest]);
        heapify_root(h, smallest);
    }
}

void heapify_leaf(heap* h, long long int i)
{
    while (i != 0 && h->arr[parent(i)].time > h->arr[i].time) {
        swap(&h->arr[i], &h->arr[parent(i)]);
        i = parent(i);
    }
}

void insert(heap* h, station s)
{
    // printf("inserting depth = %lld\t time = %lld\n",s.depth,s.time);
    // printf("size = %lld, capacity = %lld\n",h->size, h->capacity);
    if (h->size == h->capacity) {
        printf("Overflow: Could not insert\n");
        return;
    }    
    h->arr[h->size] = s;
    h->size++;

    heapify_leaf(h, h->size - 1);
}

station extract_min(heap* h)
{
    if (h->size <= 0)
        return (station){-1, -1};
    if (h->size == 1) {
        h->size--;
        return h->arr[0];
    }

    station root = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    heapify_root(h, 0);

    return root;
}

long long int cmpDepth(const void* a, const void* b)
{
    return ((station*)a)->depth - ((station*)b)->depth;
}

void print_station_arr(station* arr, long long int n)
{
    for(long long int i=0;i<n;i++)
    {
        printf("depth = %lld, time = %lld\n",arr[i].depth, arr[i].time);
    }
}

long long int main()
{
    long long int n,k,d,p;
    scanf("%lld %lld %lld %lld",&n,&k,&d,&p);
    // long long int depth[n], time[n];
    station stations[n];

    for(long long int i=0;i<n;i++)
    {
        scanf("%lld",&(stations[i].depth));
    }
    for(long long int i=0;i<n;i++)
    {
        scanf("%lld",&(stations[i].time));
    }

    qsort(stations, n , sizeof(station), cmpDepth);

    // print_station_arr(stations, n);

    long long int reachable_depth = k;
    heap* h = create_heap(n);
    long long int time =0;
    long long int prev_station_index =-1;

    while(k<d)
    {
        // add all stations to heap which are reachable
        for(long long int i=prev_station_index+1;i<n;i++)
        {
            if(stations[i].depth <= k)
            {
                // printf("inserting depth = %lld, time = %lld\n",stations[i].depth, stations[i].time);
                insert(h, stations[i]);
                prev_station_index = i;
                // printf("size = %lld\n",h->size);
            }
            else
            {
                break;
            }
        }
        // print_station_arr(h->arr, h->size);

        // if no station is reachable, print -1 and max reachable depth
        if(h->size == 0)
        {
            printf("-1 %lld\n",k);
            return 0;
        }

        else{
            station s = extract_min(h);
            k += p;
            // printf("updated k = %lld\n",k);
            time+=s.time;
            if(k>=d)
            {
                printf("%lld\n",time);
                return 0;
            }
            // printf("k = %lld, time = %lld\n",k, s.time);
        }  
    }
    if(k>=d)
        {
            printf("%lld\n",time);
            return 0;
        }

}