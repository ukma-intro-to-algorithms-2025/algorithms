#include "../include/bfs.h"
#include "../include/paths_helper.h"
#include <stdio.h>
#include <stdlib.h>

void dfs_recursive(const DigraphPtr g, PathsPtr p, vertex_t v) {
    p->marked[v] = true; 
    int size = 0;
    const vertex_t *adj = DigraphAdj(g, v, &size);
    for (int i = 0; i < size; ++i) {
        vertex_t w = adj[i];
        if (!p->marked[w]) {
            dfs_recursive(g, p, w);
            p->edge_to[w] = v; 
        }
    }
}

PathsPtr dfs(const DigraphPtr g, vertex_t s) {
    PathsPtr p = fromDigraph(g, s); 

    dfs_recursive(g, p, s); 
    return p;
}

static void dfs_postorder(const DigraphPtr g, vertex_t v, bool *visited, 
                          vertex_t *order, int *index) {
    visited[v] = true;
    int size = 0;
    const vertex_t *adj = DigraphAdj(g, v, &size);
    
    for (int i = 0; i < size; ++i) {
        vertex_t w = adj[i];
        if (!visited[w]) {
            dfs_postorder(g, w, visited, order, index);
        }
    }
    order[(*index)--] = v;
}

vertex_t *topological_sort(const DigraphPtr g) {
    if (g == NULL) {
        return NULL;
    }
    
    int V = DigraphV(g);
    if (V == 0) {
        return NULL;
    }
    
    vertex_t *order = (vertex_t *)malloc(V * sizeof(vertex_t));
    if (order == NULL) {
        return NULL;
    }
    
    bool *visited = (bool *)calloc(V, sizeof(bool));
    if (visited == NULL) {
        free(order);
        return NULL;
    }
    
    int index = V - 1;
    
    for (vertex_t v = 0; v < V; ++v) {
        if (!visited[v]) {
            dfs_postorder(g, v, visited, order, &index);
        }
    }
    
    free(visited);
    return order;
}