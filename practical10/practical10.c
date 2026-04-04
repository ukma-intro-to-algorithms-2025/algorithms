#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define M 1000         
#define TRIALS 10000  

double simulate_parking(int num_cars, int spots) {
    int *spots_taken = calloc(spots, sizeof(int));
    int total_displacement = 0;
    
    for (int car = 0; car < num_cars; car++) {
        int preferred = rand() % spots;
        int pos = preferred;
        int displaced = 0;
        
        while (pos < spots && spots_taken[pos]) {
            pos++;
            displaced++;
        }
        
        if (pos < spots) {
            spots_taken[pos] = 1;
            total_displacement += displaced;
        } else {
            total_displacement += (spots - preferred);
        }
    }
    
    free(spots_taken);
    return (double)total_displacement / num_cars;
}

void test_half_full() {
    int half_cars = M / 2;
    double sum_displacement = 0.0;
    
    for (int trial = 0; trial < TRIALS; trial++) {
        sum_displacement += simulate_parking(half_cars, M);
    }
    
    double mean_displacement = sum_displacement / TRIALS;
    double expected = 1.5;
    
    printf("\nHalf-full Case (M/2 = %d cars)\n", half_cars);
    printf("Simulated mean displacement: %.4f\n", mean_displacement);
    printf("Theoretical value:          %.4f\n", expected);
    printf("Error:                      %.4f (%.2f%%)\n", 
           fabs(mean_displacement - expected), 
           fabs((mean_displacement - expected) / expected) * 100);
}

void test_full() {
    int full_cars = M;
    double sum_displacement = 0.0;

    for (int trial = 0; trial < TRIALS; trial++) {
        sum_displacement += simulate_parking(full_cars, M);
    }

    double mean_displacement = sum_displacement / TRIALS;
    double expected = sqrt(M_PI * M / 8.0);

    printf("\nFull Case (M = %d cars)\n", full_cars);
    printf("Simulated mean displacement: %.4f\n", mean_displacement);
    printf("Theoretical value:          %.4f\n", expected);
    printf("Error:                      %.4f (%.2f%%)\n", 
           fabs(mean_displacement - expected),
           fabs((mean_displacement - expected) / expected) * 100);
}

int main() {
    srand(time(NULL));
    
    printf("Knuth's Parking Problem - Monte Carlo\n");
    printf("Spots (M): %d\n", M);
    printf("Trials:    %d\n", TRIALS);
    
    test_half_full();
    test_full();
    
    return 0;
}