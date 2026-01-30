#ifndef DYNAMIC_CONNECTIVITY_H
#define DYNAMIC_CONNECTIVITY_H

#include <stdbool.h>

typedef struct DynamicConnectivity DynamicConnectivity;

DynamicConnectivity* dc_create(int capacity);

void dc_free(DynamicConnectivity* dc);

int dc_root(DynamicConnectivity* dc, int p);

bool dc_connected(DynamicConnectivity* dc, int p, int q);

void dc_union(DynamicConnectivity* dc, int p, int q);

#endif

