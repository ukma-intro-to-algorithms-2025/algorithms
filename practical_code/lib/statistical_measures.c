#include <math.h>
#include "statistical_measures.h"

double mean(double* experiments, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += experiments[i];
    }
    return sum / n; 
}

double stddev(double* experiments, int n) {
    double m = mean(experiments, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += pow(experiments[i] - m, 2);
    }
    return sqrt(sum / (n - 1));
}

void confidence_interval(double* experiments, int n, double* ci) {
    double m = mean(experiments, n);
    double sd = stddev(experiments, n);
    double error = 1.96 * sd / sqrt(n);
    ci[0] = m - error;
    ci[1] = m + error;
}