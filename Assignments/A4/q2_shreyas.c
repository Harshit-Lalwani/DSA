#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*
each chamber has a certain minimum oxygen level limit that the diver needs to have before entering it. At the same time, after visiting each chamber, 
Percy either loses certain amount of oxygen (due to consumption) or ends up gaining some (due to presence of air pockets). 
Percy is curious and wants to know whether it will be possible for him to visit all the chambers without running out of oxygen.
Percy initially starts with k amount of oxygen. There are n chambers, where the ith chamber has a minimum oxygen requirement of xi and after visiting the chamber, his oxygen level changes by yi amount.
You have to help Percy again by letting him know whether it is possible for him to visit all the chambers in any order without running out of oxygen. He can visit one chamber only once.

* n : number of chambers
* k : initial oxygen amt
* x[i] : required oxygen amt for each chamber i
* y[i] : oxygen amt lost per chamber i
*/

struct Chamber {
    int oxygen;
    int loss;
};

typedef struct Chamber chamber;

int compare(const void* a, const void* b) {
    return ((chamber*)a)->oxygen - ((chamber*)b)->oxygen;
}

typedef struct BinaryHeap{
    chamber* arr;
    int capacity;
    int size;
} binaryheap;

binaryheap* createBinaryHeap(int capacity) {
    binaryheap* bh = (binaryheap*)malloc(sizeof(struct BinaryHeap));
    bh->arr = (chamber*)malloc(capacity * sizeof(chamber));
    bh->capacity = capacity;
    bh->size = 0;
    return bh;
}

void swap(chamber* a, chamber* b) {
    chamber temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(binaryheap* bh, int i) {
    //! heapifies based on oxygen levels
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < bh->size && bh->arr[left].oxygen > bh->arr[largest].oxygen) largest = left;
    if(right < bh->size && bh->arr[right].oxygen > bh->arr[largest].oxygen) largest = right;

    if(largest != i) {
        swap(&bh->arr[i], &bh->arr[largest]);
        heapify(bh, largest);
    }
}

void insert(binaryheap* bh, chamber data) {
    //! inserts based on oxygen levels
    if(bh->size == bh->capacity) return;
    bh->arr[bh->size] = data;
    int i = bh->size;
    bh->size++;

    while(i > 0 && bh->arr[i].oxygen > bh->arr[(i-1)/2].oxygen) {
        swap(&bh->arr[i], &bh->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

chamber extractMax(binaryheap* bh) {
    //! extracts based on oxygen levels
    chamber max = bh->arr[0];
    bh->arr[0] = bh->arr[bh->size-1];
    bh->size--;
    heapify(bh, 0);
    return max;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if(n == 0) {
        printf("YES\n");
        return 0;
    }

    chamber nodes[n];
    for(int i=0;i<n;i++) scanf("%d", &nodes[i].oxygen);
    for(int i=0;i<n;i++) scanf("%d", &nodes[i].loss); 
    qsort(nodes, n, sizeof(chamber), compare);
    binaryheap* bh = createBinaryHeap(n);
    int ptr=0;
    while(ptr < n){
        if(nodes[ptr].loss >= 0 && nodes[ptr].oxygen <= k) k+=nodes[ptr++].loss;
        else insert(bh, nodes[ptr++]);
    }

    while(bh->size > 0) {
        chamber temp = extractMax(bh);
        if(k < temp.oxygen || k < 0) {
            printf("NO\n");
            return 0;
        }
        k += temp.loss;
    }

    if(k < 0) printf("NO\n");
    else printf("YES\n");
    return 0;
}