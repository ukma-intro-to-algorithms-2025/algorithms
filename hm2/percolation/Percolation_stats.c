#include "Percolation_stats.h"
#include "percolation.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

PercolationStats* create_percolation_stats(int grid_size, int experiments) {
    if (grid_size <= 0 || experiments <= 0) return NULL;

    PercolationStats* ps = malloc(sizeof(PercolationStats));
    if (!ps) return NULL;

    ps->n = grid_size; //розмір сітки
    ps->T = experiments; //кількість експериментів
    ps->thresholds = malloc(sizeof(double) * experiments); //память для порогів перколяції

    if (!ps->thresholds) {
        free(ps);
        return NULL;
    }

    return ps;
}

void destroy_percolation_stats(PercolationStats* ps) {
    if (!ps) return;
    free(ps->thresholds);
    free(ps);
}

void run_experiments(PercolationStats* ps) {
    if (!ps) return;

    srand((unsigned)time(NULL));  //випадкові числа

    int n = ps->n; //розмір сітки
    int total = n * n;  //комірки у сітці

    for (int i = 0; i < ps->T; i++) {
        Percolation* p = percolation_create(n); 

        while (!percolation_percolates(p)) { //відкриття випадкових клітинок
            int row = rand() % n; //випадковий рядок
            int col = rand() % n; //випадковий стовпець

            if (!percolation_is_open(p, row, col)) {
                percolation_open(p, row, col);
            }
        }

        ps->thresholds[i]=(double)percolation_number_of_open_sites(p) / total; //обчислення порогу, відкриті/загальна кількість

        percolation_destroy(p);
    }
}

double mean_percolation_threshold(PercolationStats* ps) { //середнє значення 
    if (!ps || ps->T == 0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < ps->T; i++) {
        sum += ps->thresholds[i]; //кожне значення порогу
    }
    return sum / ps->T; //середнє
}

double stddev_percolation_threshold(PercolationStats* ps) { //стандартне відхилення
    if (!ps || ps->T <= 1) return 0.0; 

    double mean = mean_percolation_threshold(ps); 
    double sum = 0.0;

    for (int i = 0; i < ps->T; i++) {
        double diff = ps->thresholds[i] - mean; //різниця від середнього
        sum += diff * diff; //квадрат різниці від середнього
    }

    return sqrt(sum / (ps->T - 1));
}

void print_statistics(PercolationStats* ps) {
    if (!ps) return;

    double mean = mean_percolation_threshold(ps); //середнє значення порогу
    double stddev = stddev_percolation_threshold(ps); //середнє відхилення
    double delta = 1.96 * stddev / sqrt(ps->T); //похибка 95% інтервалу

    printf("Mean percolation threshold: %.10f\n", mean);
    printf("Standard deviation: %.10f\n", stddev);
    printf("95%% confidence interval: [%.10f, %.10f]\n",
           mean - delta, mean + delta);
}
