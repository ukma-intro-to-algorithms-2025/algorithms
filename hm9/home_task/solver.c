#include "maze.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    pair_t *data;
    int head, tail, size;
} Queue;

Queue* q_create(int cap) {
    Queue *q = malloc(sizeof(Queue));
    q->data = malloc(cap * sizeof(pair_t));
    q->head = q->tail = 0;
    q->size = cap;
    return q;
}
void q_push(Queue *q, pair_t p) { q->data[q->tail++] = p; }
pair_t q_pop(Queue *q) { return q->data[q->head++]; }
bool q_is_empty(Queue *q) { return q->head == q->tail; }
void q_free(Queue *q) { free(q->data); free(q); }
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// task 1 
pair_t* GraphShortestBFS(MazePtr m, pair_t start, pair_t end, int *path_len, int *visited_nodes) {
    int size = MazeGetSize(m);
    char **grid = MazeGetPoints(m);
    *visited_nodes = 0;

    pair_t **parent = malloc(size * sizeof(pair_t*));
    bool **visited = malloc(size * sizeof(bool*));
    for(int i = 0; i < size; i++) {
        parent[i] = malloc(size * sizeof(pair_t));
        visited[i] = calloc(size, sizeof(bool));
        for(int j = 0; j < size; j++) parent[i][j] = (pair_t){-1, -1};
    }

    Queue *q = q_create(size * size);
    q_push(q, start);
    visited[start.x][start.y] = true;

    bool found = false;
    while(!q_is_empty(q)) {
        pair_t curr = q_pop(q);
        (*visited_nodes)++;
        if(curr.x == end.x && curr.y == end.y) { found = true; break; }

        for(int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];
            if(nx >= 0 && nx < size && ny >= 0 && ny < size && grid[nx][ny] != OBSTACLE && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = curr;
                q_push(q, (pair_t){nx, ny});
            }
        }
    }

    pair_t *path = NULL;
    if(found) {
        int len = 0;
        pair_t temp = end;
        while(temp.x != -1) { len++; temp = parent[temp.x][temp.y]; }
        *path_len = len;
        path = malloc(len * sizeof(pair_t));
        temp = end;
        for(int i = len-1; i >= 0; i--) { path[i] = temp; temp = parent[temp.x][temp.y]; }
    }

    for(int i = 0; i < size; i++) { free(parent[i]); free(visited[i]); }
    free(parent); free(visited); q_free(q);
    return path;
}

// task 2
bool dfs_helper(MazePtr m, pair_t curr, pair_t end, bool **vis, pair_t **par, int *count) {
    int size = MazeGetSize(m);
    char **grid = MazeGetPoints(m);
    vis[curr.x][curr.y] = true;
    (*count)++;
    if(curr.x == end.x && curr.y == end.y) return true;

    for(int i = 0; i < 4; i++) {
        int nx = curr.x + dx[i], ny = curr.y + dy[i];
        if(nx >= 0 && nx < size && ny >= 0 && ny < size && grid[nx][ny] != OBSTACLE && !vis[nx][ny]) {
            par[nx][ny] = curr;
            if(dfs_helper(m, (pair_t){nx, ny}, end, vis, par, count)) return true;
        }
    }
    return false;
}

pair_t* GraphPathDFS(MazePtr m, pair_t start, pair_t end, int *path_len, int *visited_nodes) {
    int size = MazeGetSize(m);
    *visited_nodes = 0;
    bool **vis = malloc(size * sizeof(bool*));
    pair_t **par = malloc(size * sizeof(pair_t*));
    for(int i = 0; i < size; i++) {
        vis[i] = calloc(size, sizeof(bool));
        par[i] = malloc(size * sizeof(pair_t));
        for(int j = 0; j < size; j++) par[i][j] = (pair_t){-1, -1};
    }

    pair_t *path = NULL;
    if(dfs_helper(m, start, end, vis, par, visited_nodes)) {
        int len = 0; pair_t temp = end;
        while(temp.x != -1) { len++; temp = par[temp.x][temp.y]; }
        *path_len = len;
        path = malloc(len * sizeof(pair_t));
        temp = end;
        for(int i = len-1; i >= 0; i--) { path[i] = temp; temp = par[temp.x][temp.y]; }
    }

    for(int i = 0; i < size; i++) { free(vis[i]); free(par[i]); }
    free(vis); free(par);
    return path;
}

// aditional task 1
pair_t* FindNearestLampBFS(MazePtr m, pair_t start, int *path_len, int *visited_nodes) {
    int size = MazeGetSize(m);
    char **grid = MazeGetPoints(m);
    *visited_nodes = 0;

    pair_t **parent = malloc(size * sizeof(pair_t*));
    bool **visited = malloc(size * sizeof(bool*));
    for(int i = 0; i < size; i++) {
        parent[i] = malloc(size * sizeof(pair_t));
        visited[i] = calloc(size, sizeof(bool));
        for(int j = 0; j < size; j++) parent[i][j] = (pair_t){-1, -1};
    }

    Queue *q = q_create(size * size);
    q_push(q, start);
    visited[start.x][start.y] = true;

    pair_t found_lamp = {-1, -1};
    while(!q_is_empty(q)) {
        pair_t curr = q_pop(q);
        (*visited_nodes)++;
        if(grid[curr.x][curr.y] == DEST) { found_lamp = curr; break; }

        for(int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];
            if(nx >= 0 && nx < size && ny >= 0 && ny < size && grid[nx][ny] != OBSTACLE && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = curr;
                q_push(q, (pair_t){nx, ny});
            }
        }
    }

    pair_t *path = NULL;
    if(found_lamp.x != -1) {
        int len = 0; pair_t temp = found_lamp;
        while(temp.x != -1) { len++; temp = parent[temp.x][temp.y]; }
        *path_len = len;
        path = malloc(len * sizeof(pair_t));
        temp = found_lamp;
        for(int i = len-1; i >= 0; i--) { path[i] = temp; temp = parent[temp.x][temp.y]; }
    }

    for(int i = 0; i < size; i++) { free(parent[i]); free(visited[i]); }
    free(parent); free(visited); q_free(q);
    return path;
}