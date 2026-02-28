#include "priority_queue.h"

#include <assert.h>
#include <stdio.h>

void sink(Item *a, int k, int N) {
    while (2 * k + 1 <= N - 1) { 
        int j = 2 * k + 1;       
        if (j + 1 <= N - 1 && less(a[j], a[j + 1])) {
            j++;
        }
        if (!less(a[k], a[j])) {
            break;
        }
        exch(a[k], a[j]);
        k = j;
    }
}

void heapsort(Item *a, int N) {
    for (int k = N / 2 - 1; k >= 0; k--) {
        sink(a, k, N);
    }
    while (N > 1) {
        exch(a[0], a[N - 1]); 
        N--;
        sink(a, 0, N);
    }
}

int main() {
    printf("Testing heapsort with 0-indexed arrays:\n");

    {
        char *arr[] = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
        int N = sizeof(arr) / sizeof(arr[0]);

        printf("Original array: ");
        for (int i = 0; i < N; i++) {
            printf("%s ", arr[i]);
        }
        printf("\n");

        heapsort((Item *)arr, N);

        printf("Sorted array:   ");
        for (int i = 0; i < N; i++) {
            printf("%s ", arr[i]);
        }
        printf("\n");

        char *expected[] = {"A", "E", "E", "L", "M", "O", "P", "R", "S", "T", "X"};
        for (int i = 0; i < N; i++) {
            assert(strcmp(arr[i], expected[i]) == 0);
        }
        printf("Test 1 passed!\n\n");
    }

    {
        char *arr[] = {"S", "A", "F"};
        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N);

        char *expected[] = {"A", "F", "S"};
        for (int i = 0; i < N; i++) {
            assert(strcmp(arr[i], expected[i]) == 0);
        }
        printf("Test 2 passed!\n");
    }

    {
        char *arr[] = {"X"};
        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N);

        assert(strcmp(arr[0], "X") == 0);
        printf("Test 3 passed!\n");
    }

    {
        char *arr[] = {"X", "Y"};
        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N);

        assert(strcmp(arr[0], "X") == 0);
        assert(strcmp(arr[1], "Y") == 0);
        printf("Test 4 passed!\n");
    }

    {
        char *arr[] = {"X", "Z", "Y"};
        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N);

        assert(strcmp(arr[0], "X") == 0);
        assert(strcmp(arr[1], "Y") == 0);
        assert(strcmp(arr[2], "Z") == 0);
        printf("Test 5 passed!\n");
    }

    return 0;
}