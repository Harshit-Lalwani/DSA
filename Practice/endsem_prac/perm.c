#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int* array, int start, int end) {
    if (start == end) { //if start = end, print string
        for (int i = 0; i <= end; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    } else {
        for (int i = start; i <= end; i++) {
            swap((array+i), (array+start));
            permute(array, start+1, end);
            swap((array+i), (array+start)); // backtrack
        }
    }
}

int main() {
    int array[] = {1,1, 2, 3};
    int n = sizeof(array) / sizeof(array[0]);
    permute(array, 0, n-1);
    return 0;
}