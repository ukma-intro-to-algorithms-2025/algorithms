#include <assert.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define N 10
#define CUTOFF 10
typedef char Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B)                                                                                 \
    {                                                                                              \
        Item t = A;                                                                                \
        A = B;                                                                                     \
        B = t;                                                                                     \
    }

void print_items(Item a[], int lo, int hi) {
    for (int i = lo; i <= hi; i++) {
        printf("%c ", a[i]);
    }
    printf("\n");
}

void generate_items(Item a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = (rand() % 26) + 'A';
    }
}

void insertion_sort(Item a[], int l, int r) {
    int i, j;
    for (i = l; i <= r; ++i) {
        for (j = i; j > l; --j) {
            if (less(a[j], a[j - 1])) {
                exch(a[j], a[j - 1]);
            } else {
                break;
            }
        }
    }
}

void shuffle(Item a[], int size) {
    for (int i = 0; i < size; ++i) {
        int r = rand() % (i + 1);
        exch(a[i], a[r]);
    }
}

int medianOf3(Item arr[], int lo, int mid, int hi) {
    if ((less(arr[lo], arr[mid]) && less(arr[mid], arr[hi])) ||
        (less(arr[hi], arr[mid]) && less(arr[mid], arr[lo]))) {
        return mid;
    }
    if ((less(arr[mid], arr[lo]) && less(arr[lo], arr[hi])) ||
        (less(arr[hi], arr[lo]) && less(arr[lo], arr[mid]))) {
        return lo;
    }
    return hi;
}

int partition(Item arr[], int lo, int hi) {
    int i = lo, j = hi + 1;
    Item pivot = arr[lo];

    while (true) {
        while (less(arr[++i], pivot))
            if (i == hi) break;

        while (less(pivot, arr[--j]))
            if (j == lo) break;

        if (i >= j) break;
        exch(arr[i], arr[j]);
    }

    exch(arr[lo], arr[j]);
    return j;
}

void quicksort_impl(Item arr[], int lo, int hi) {
    if (hi <= lo + CUTOFF - 1) {
        insertion_sort(arr, lo, hi); 
        return;
    }

    int m = medianOf3(arr, lo, lo + (hi - lo) / 2, hi);
    exch(arr[lo], arr[m]);

    int j = partition(arr, lo, hi);
    quicksort_impl(arr, lo, j - 1);
    quicksort_impl(arr, j + 1, hi);
}

void quicksort(Item arr[], int n) {
    shuffle(arr, n);
    quicksort_impl(arr, 0, n - 1);
}

Item quick_select(Item arr[], int size, int k) {
    shuffle(arr, size);
    int lo = 0;
    int hi = size - 1;
    while (hi > lo) {
        int j = partition(arr, lo, hi);
        if (j < k)
            lo = j + 1;
        else if (j > k)
            hi = j - 1;
        else
            return arr[k];
    }
    return arr[k];
}

void quicksort_3way_impl(Item arr[], int lo, int hi) {
    if (hi <= lo + CUTOFF - 1) {
        insertion_sort(arr, lo, hi);
        return;
    }

    int m = medianOf3(arr, lo, lo + (hi - lo) / 2, hi);
    exch(arr[lo], arr[m]);
    Item v = arr[lo];
    int lt = lo, gt = hi;
    int i = lo;

    while (i <= gt) {
        if (less(arr[i], v)) {
            exch(arr[lt], arr[i]); lt++; i++;
        } else if (less(v, arr[i])) {
            exch(arr[i], arr[gt]); gt--;
        } else { i++; }
    }
    quicksort_3way_impl(arr, lo, lt - 1);
    quicksort_3way_impl(arr, gt + 1, hi);
}

void quicksort_3way(Item arr[], int n) {
    shuffle(arr, n);
    quicksort_3way_impl(arr, 0, n - 1);
}

void sort_duplicates(int n, void (*sort_func)(Item[], int), const char* name) {
    Item *arr = malloc(2 * n * sizeof(Item));

    int i = 0;
    
    for (i = 0; i < n; ++i)
        arr[i] = 'A' + (i % 26);

    for (; i < 2 * n; ++i)
        arr[i] = 'B' + ((2 * n - i - 1) % 26);

    clock_t start = clock();
    sort_func(arr, 2 * n);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time for %s with %d elements: %f seconds\n", name, 2 * n, time_spent);
    
    free(arr);
}

int compare(const void *a, const void *b) { return (*(Item *)a - *(Item *)b); }

void quicksort_standard(Item arr[], int n) { qsort(arr, n, sizeof(Item), compare); }

int main() {
    {
        printf("Partition\n");
        Item a[] = {'K', 'R', 'A', 'T', 'E', 'L', 'E', 'P', 'U', 'I', 'M', 'Q', 'C', 'X', 'O', 'S'};
        int size = sizeof(a) / sizeof(a[0]);
        printf("Number of elements: %d\n", size);
        printf("Original array: \n");
        print_items(a, 0, size - 1);
        int partition_idx = partition(a, 0, size - 1);
        printf("partition_idx = %d, a[partition_idx] = %c\n", partition_idx, a[partition_idx]);
        printf("Array after one partition(): \n");
        print_items(a, 0, size - 1);
    }

    printf("\n");

    {
        printf("Quicksort\n");
        Item a[] = {'K', 'R', 'A', 'T', 'E', 'L', 'E', 'P', 'U', 'I', 'M', 'Q', 'C', 'X', 'O', 'S'};
        int size = sizeof(a) / sizeof(a[0]);
        printf("Original array: \n");
        print_items(a, 0, size - 1);
        quicksort(a, size);
        printf("Array after quicksort(): \n");
        print_items(a, 0, size - 1);
    }

    printf("\n");

    {
        printf("Selection\n");
        Item a[] = {'K', 'R', 'A', 'T', 'E', 'L', 'E', 'P', 'U', 'I', 'M', 'Q', 'C', 'X', 'O', 'S'};
        int size = sizeof(a) / sizeof(a[0]);
        printf("Original array: \n");
        print_items(a, 0, size - 1);
        printf("%d-th=%c, %d-th=%c, %d-th=%c\n", 0, quick_select(a, size, 0), 7,
               quick_select(a, size, 7), 15, quick_select(a, size, 15));
    }

    printf("\n");

    { 
        printf("Порівняння продуктивності (після виправлення):\n");
        sort_duplicates(2000000, quicksort, "quicksort");
        sort_duplicates(4000000, quicksort, "quicksort");
        sort_duplicates(8000000, quicksort, "quicksort");
        
        sort_duplicates(2000000, quicksort_3way, "quicksort 3-way");
        sort_duplicates(4000000, quicksort_3way, "quicksort 3-way");
        sort_duplicates(8000000, quicksort_3way, "quicksort 3-way");
    }

    return 0;
}