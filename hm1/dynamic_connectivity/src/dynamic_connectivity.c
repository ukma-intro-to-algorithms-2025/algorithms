#include "dynamic_connectivity.h"
#include <stdlib.h>
#include <stdbool.h>

struct DynamicConnectivity {
    int capacity;
    int* parent;
    int* size;
};

DynamicConnectivity* dc_create(int capacity) {
    if (capacity <= 0) return NULL;

    DynamicConnectivity* dc = (DynamicConnectivity*)malloc(sizeof(DynamicConnectivity));
    if (!dc) return NULL;

    dc->capacity = capacity;
    dc->parent = (int*)malloc(sizeof(int) * capacity);
    dc->size   = (int*)malloc(sizeof(int) * capacity);

    if (!dc->parent || !dc->size) {
        free(dc->parent);
        free(dc->size);
        free(dc);
        return NULL;
    }

    for (int i = 0; i < capacity; i++) {
        dc->parent[i] = i;
        dc->size[i] = 1;
    }

    return dc;
}

void dc_free(DynamicConnectivity* dc) {
    if (!dc) return;

    free(dc->parent);
    free(dc->size);
    free(dc);
}

int dc_root(DynamicConnectivity* dc, int p) {
    if (!dc || p < 0 || p >= dc->capacity) return -1;

    while (p != dc->parent[p]) {
        dc->parent[p] = dc->parent[dc->parent[p]];
        p = dc->parent[p];
    }
    return p;
}

bool dc_connected(DynamicConnectivity* dc, int p, int q) {
    if (!dc) return false;
    return dc_root(dc, p) == dc_root(dc, q);
}

void dc_union(DynamicConnectivity* dc, int p, int q) {
    if (!dc) return;

    int rootP = dc_root(dc, p);
    int rootQ = dc_root(dc, q);

    if (rootP == rootQ) return;

    if (dc->size[rootP] < dc->size[rootQ]) {
        dc->parent[rootP] = rootQ;
        dc->size[rootQ] += dc->size[rootP];
    } else {
        dc->parent[rootQ] = rootP;
        dc->size[rootP] += dc->size[rootQ];
    }
}
