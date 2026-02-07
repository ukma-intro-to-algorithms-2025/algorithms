#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    double salary;
} Employee;

void exch(void *a, void *b, size_t size) {
    char *ptr_a = (char *)a;
    char *ptr_b = (char *)b;
    char temp;
    
    for (size_t i = 0; i < size; i++) {
        temp = ptr_a[i];
        ptr_a[i] = ptr_b[i];
        ptr_b[i] = temp;
    }
}

void shell_sort(void *arr, int N, size_t size, int (*cmp)(const void *, const void *)) {
    int h = 1;
    while (h < N / 3) {
        h = 3 * h + 1;
    }  
    while (h >= 1) {
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h; j -= h) {
                void *elem_j = (char *)arr + j * size;
                void *elem_j_minus_h = (char *)arr + (j - h) * size;
                
                if (cmp(elem_j, elem_j_minus_h) < 0) {
                    exch(elem_j, elem_j_minus_h, size);
                } else {
                    break;
                }
            }
        }
        h /= 3;
    }
}

int compare_by_age_asc(const void *a, const void *b) {
    return ((Employee *)a)->age - ((Employee *)b)->age;
}

int compare_by_salary_asc(const void *a, const void *b) {
    double diff = ((Employee *)a)->salary - ((Employee *)b)->salary;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int compare_by_name_asc(const void *a, const void *b) {
    return strcmp(((Employee *)a)->name, ((Employee *)b)->name);
}

void print_employees(Employee *employees, int N) {
    for (int i = 0; i < N; i++) {
        printf("%s, Age: %d, Salary: %.2f\n", 
               employees[i].name, 
               employees[i].age,
               employees[i].salary);
    }
}

int main() {
    Employee employees[] = {
        {"Alice", 25, 50000}, 
        {"Bob", 30, 70000}, 
        {"Charlie", 22, 45000}, 
        {"Dave", 35, 80000}
    };

    int N = sizeof(employees) / sizeof(employees[0]);
    Employee employees_copy[4];

    printf("Sorted by Age:\n");
    memcpy(employees_copy, employees, sizeof(employees));
    shell_sort(employees_copy, N, sizeof(Employee), compare_by_age_asc);
    print_employees(employees_copy, N);
    printf("\n");
    printf("Sorted by Salary:\n");
    memcpy(employees_copy, employees, sizeof(employees));
    shell_sort(employees_copy, N, sizeof(Employee), compare_by_salary_asc);
    print_employees(employees_copy, N);
    printf("\n");
    printf("Sorted by Name:\n");
    memcpy(employees_copy, employees, sizeof(employees));
    shell_sort(employees_copy, N, sizeof(Employee), compare_by_name_asc);
    print_employees(employees_copy, N);
    printf("\n");

    return 0;
}