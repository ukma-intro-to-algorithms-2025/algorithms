#ifndef PERCOLATION_STATS_H
#define PERCOLATION_STATS_H
#include <stdlib.h> 
typedef struct {
 int n; 
 int T;
 double* thresholds; //зберігання порогій пероколяції 
} PercolationStats;

PercolationStats* create_percolation_stats(int grid_size, int
experiments);    //створення та ініціалізація 
void destroy_percolation_stats(PercolationStats* ps); //знищення

double mean_percolation_threshold(PercolationStats* ps); //середнє значення порогів

double stddev_percolation_threshold(PercolationStats* ps); //обчислення стандартного відхилення порогів

void run_experiments(PercolationStats* ps); //запуск експериментів монте-карло та збереження результатів

void print_statistics(PercolationStats* ps); //статистика

#endif 
