#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <stdbool.h>
#include "../../dynamic_connectivity/src/dynamic_connectivity.h"

typedef struct {
    int n;
    bool* open;
    int open_count;
    int top;
    int bottom;
    DynamicConnectivity* uf;  
} Percolation;

Percolation* percolation_create(int n);
void percolation_open(Percolation* p, int row, int col);
bool percolation_is_open(Percolation* p, int row, int col);
bool percolation_percolates(Percolation* p);
int percolation_number_of_open_sites(Percolation* p);
void percolation_destroy(Percolation* p);

#endif