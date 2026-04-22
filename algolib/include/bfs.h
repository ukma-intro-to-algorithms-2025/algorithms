#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include <stdbool.h>

typedef struct Paths {
    int vertices;
    bool *marked;
    vertex_t *edge_to;
} Paths;

typedef Paths *PathsPtr;

PathsPtr bfs(const GraphPtr g, vertex_t s);
bool hasPathTo(PathsPtr p, vertex_t v);
vertex_t* pathTo(PathsPtr p, vertex_t v, int *len);
void destroyPaths(PathsPtr p);

#endif