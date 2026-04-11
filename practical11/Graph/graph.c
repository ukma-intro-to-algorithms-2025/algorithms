#include "graph.h"
#include "paths_helper.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    vertex_t *neighbors;
    int size;
    int capacity;
} Vector;

#define INITIAL_CAPACITY 4

static int add_adjacent_vertex(Vector *list, vertex_t v) {
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity == 0 ? INITIAL_CAPACITY : list->capacity * 2;
        vertex_t *new_data = realloc(list->neighbors, new_capacity * sizeof(vertex_t));
        if (new_data == NULL)
            return 0;
        list->neighbors = new_data;
        list->capacity = new_capacity;
    }
    list->neighbors[list->size++] = v;
    return 1;
}

struct Graph {
    vertex_t V;
    edge_t E;
    Vector *adj;
};

GraphPtr GraphInit(vertex_t num_vertices) {
    GraphPtr g = malloc(sizeof(struct Graph));
    if (g == NULL)
        return NULL;

    g->V = num_vertices;
    g->E = 0;

    g->adj = calloc(num_vertices, sizeof(Vector));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

GraphPtr GraphInitFromFile(FILE *in) {
    if (in == NULL)
        return NULL;

    int V, E;
    if (fscanf(in, "%d", &V) != 1)
        return NULL;
    if (fscanf(in, "%d", &E) != 1)
        return NULL;

    GraphPtr g = GraphInit(V);
    if (g == NULL)
        return NULL;

    for (int i = 0; i < E; i++) {
        int v, w;
        if (fscanf(in, "%d %d", &v, &w) != 2) {
            GraphDestroy(g);
            return NULL;
        }
        GraphAddEdge(g, v, w);
    }

    return g;
}

void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w) {
    if (g == NULL || v >= g->V || w >= g->V)
        return;

    if (!add_adjacent_vertex(&g->adj[v], w))
        return;
    if (!add_adjacent_vertex(&g->adj[w], v))
        return;

    g->E++;
}

vertex_t GraphV(const GraphPtr g) { return (g != NULL) ? g->V : 0; }

edge_t GraphE(const GraphPtr g) { return (g != NULL) ? g->E : 0; }

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size) {
    if (g == NULL || v >= g->V || size == NULL)
        return NULL;

    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

void GraphPrint(const GraphPtr g) {
    if (g == NULL)
        return;

    for (vertex_t v = 0; v < g->V; v++) {
        printf("%d:", v);
        for (int i = 0; i < g->adj[v].size; i++) {
            printf(" %d", g->adj[v].neighbors[i]);
        }
        printf("\n");
    }
}

void GraphDestroy(GraphPtr g) {
    if (g == NULL)
        return;

    for (vertex_t v = 0; v < g->V; v++) {
        free(g->adj[v].neighbors);
    }
    free(g->adj);
    free(g);
}

static vertex_t *ShortestDFS(const GraphPtr g, vertex_t current, vertex_t end, vertex_t *path,
                             int path_len, vertex_t *shortest, int *shortest_len, int max_len,
                             char *visited) {
    if (path_len >= max_len)
        return shortest;

    path[path_len] = current;
    path_len++;
    visited[current] = 1;

    if (current == end) {
        if (*shortest_len == -1 || path_len < *shortest_len) {
            *shortest_len = path_len;
            for (int i = 0; i < path_len; i++) {
                shortest[i] = path[i];
            }
            printf("Found path:\n");
            printPath(path, path_len);
        }
    } else {
        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);
        for (int i = 0; i < size; i++) {
            vertex_t w = adj[i];
            if (!visited[w]) {
                if (*shortest_len == -1 || path_len < *shortest_len) {
                    shortest = ShortestDFS(g, w, end, path, path_len, shortest, shortest_len, max_len, visited);
                }
            }
        }
    }

    visited[current] = 0;
    return shortest;
}

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len) {
    if (g == NULL || path_len == NULL) {
        if (path_len) *path_len = 0;
        return NULL;
    }
    
    if (start < 0 || start >= GraphV(g) || end < 0 || end >= GraphV(g)) {
        *path_len = 0;
        return NULL;
    }
    
    int V = GraphV(g);
    int max_len = V;
    
    vertex_t *path = malloc(V * sizeof(vertex_t));
    vertex_t *shortest = malloc(V * sizeof(vertex_t));
    char *visited = calloc(V, sizeof(char));
    
    if (path == NULL || shortest == NULL || visited == NULL) {
        free(path);
        free(shortest);
        free(visited);
        *path_len = 0;
        return NULL;
    }
    
    int shortest_len = -1;
    
    ShortestDFS(g, start, end, path, 0, shortest, &shortest_len, max_len, visited);
    
    free(path);
    free(visited);
    
    if (shortest_len == -1) {
        free(shortest);
        *path_len = 0;
        return NULL;
    }
    
    *path_len = shortest_len;
    return shortest;
}