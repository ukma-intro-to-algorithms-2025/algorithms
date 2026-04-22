#include "../include/bfs.h"
#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h>

static void bfs_search(const GraphPtr g, PathsPtr p, vertex_t s) {
    QueuePtr q = QueueCreate();
    
    p->marked[s] = true;
    QueueEnqueue(q, (void*)(size_t)s);
    
    while (!QueueIsEmpty(q)) {
        vertex_t v = (vertex_t)(size_t)QueueDequeue(q);
        int size = 0;
        const vertex_t *adj = GraphAdj(g, v, &size);
        
        for (int i = 0; i < size; ++i) {
            vertex_t w = adj[i];
            if (!p->marked[w]) {
                QueueEnqueue(q, (void*)(size_t)w);
                p->marked[w] = true;
                p->edge_to[w] = v;
            }
        }
    }
    
    QueueDestroy(q);
}

PathsPtr bfs(const GraphPtr g, vertex_t s) {
    if (g == NULL) return NULL;
    
    int V = GraphV(g);
    
    PathsPtr p = malloc(sizeof(Paths));
    if (!p) return NULL;
    
    p->vertices = V;
    p->marked = calloc(V, sizeof(bool));
    p->edge_to = malloc(V * sizeof(vertex_t));
    
    if (!p->marked || !p->edge_to) {
        free(p->marked);
        free(p->edge_to);
        free(p);
        return NULL;
    }
    
    // Ініціалізуємо edge_to
    for (int i = 0; i < V; i++) {
        p->edge_to[i] = -1;
    }
    
    bfs_search(g, p, s);
    
    return p;
}

bool hasPathTo(PathsPtr p, vertex_t v) {
    if (!p || v < 0 || v >= p->vertices) return false;
    return p->marked[v];
}

vertex_t* pathTo(PathsPtr p, vertex_t v, int *len) {
    if (!p || !hasPathTo(p, v)) {
        if (len) *len = 0;
        return NULL;
    }
    
    int count = 0;
    for (vertex_t x = v; x != -1; x = p->edge_to[x]) {
        count++;
    }
    
    vertex_t *path = malloc(count * sizeof(vertex_t));
    if (!path) return NULL;
    
    int idx = count - 1;
    for (vertex_t x = v; x != -1; x = p->edge_to[x]) {
        path[idx--] = x;
    }
    
    if (len) *len = count;
    return path;
}

void destroyPaths(PathsPtr p) {
    if (!p) return;
    free(p->marked);
    free(p->edge_to);
    free(p);
}