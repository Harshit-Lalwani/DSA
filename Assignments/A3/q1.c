//you are given an array of n integers. you have to find the length of the largest subarray such that all the elements in the subarray are consecutive integers.
//print the length of the subarray and the indices of the subarray


// Constraints:
// 1 <= n <= 2 ⋅ 10^5

// 1 <= arr[i] <= 10^9


#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300000

typedef struct {
    int key;
    int value;
} hash_item;

typedef struct {
    hash_item* items[MAX_N];
} hash_table;

hash_table* create_hash_table() {
    hash_table* ht = malloc(sizeof(hash_table));
    for(int i = 0; i < MAX_N; i++) {
        ht->items[i] = NULL;
    }
    return ht;
}

void insert(hash_table* ht, int key, int value) {
    hash_item* item = malloc(sizeof(hash_item));
    item->key = key;
    item->value = value;
    int hash_index = key % MAX_N;
    ht->items[hash_index] = item;
}

int search(hash_table* ht, int key) {
    int hash_index = key % MAX_N;
    if(ht->items[hash_index] != NULL) {
        return ht->items[hash_index]->value;
    } else {
        return -1;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    hash_table* ls = create_hash_table();
    hash_table* count = create_hash_table();

    int n;
    int largest_num;
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max_count = 0;

    for(int i = 0; i < n; i++) {
        if(i == 0) {
            insert(ls, arr[i], arr[i]);
            insert(count, arr[i], 1);
            if(max_count < 1) {
                max_count = 1;                
                largest_num = arr[i];
            }
        } else if(search(ls, arr[i] - 1) != -1) {
            insert(ls, arr[i], search(ls, arr[i] - 1));
            insert(count, search(ls, arr[i]), search(count, search(ls, arr[i])) + 1);
            if(search(count, search(ls, arr[i])) > max_count) {
                max_count = search(count, search(ls, arr[i]));
                largest_num = arr[i];
            }
        } else {
            insert(ls, arr[i], arr[i]);
            insert(count, arr[i], 1);
            max_count = max(max_count, 1);
            if(max_count < 1) {
                max_count = 1;
                largest_num = arr[i];
            }
        }
        printf("i= %d, max_count = %d, largest_num = %d, arr[i] = %d\n", i, max_count, largest_num, arr[i]);
    }

    printf("%d\n", max_count);


    int out[max_count];
    int prev_index = n;

    printf("largest_num = %d\n", largest_num);

    for(int i = max_count - 1; i >= 0; i--) {
        for(int j = prev_index - 1; j >= 0; j--) {
            if(arr[j] == largest_num) {
                printf("prev_index = %d\n", prev_index);
                printf("arr[%d] = %d\n",j, arr[j]);
                out[i] = j;
                prev_index = j;
                break;
            }
        }
        largest_num--;
    }

    for(int i = 0; i < max_count; i++) {
        printf("%d ", out[i]);
    }

    printf("\n");

    free(ls);
    free(count);

    return 0;
}