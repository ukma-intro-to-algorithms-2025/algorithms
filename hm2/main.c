#include <stdio.h>
#include <stdlib.h>
#include "percolation_stats.h"

int main(int argc, char* argv[]) {
    if (argc != 3) { 
        printf("Usage: %s n T\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); //перетворення 1 аргументу у розмір сітки
    int T = atoi(argv[2]); //перетворення 2 аргументу у кількість експериментів

    if (n <= 0 || T <= 0) { //перевірка значень
        printf("n and T must be positive integers\n");
        return 1;
    }

    PercolationStats* ps = create_percolation_stats(n, T);
    if (!ps) {
        printf("Failed to create PercolationStats\n");
        return 1;
    }

    run_experiments(ps);
    print_statistics(ps);
    destroy_percolation_stats(ps);

    return 0;
}
//atoi - рядок у ціле число