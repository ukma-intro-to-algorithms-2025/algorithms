#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

void print_result(const char* label, pair_t* path, int len, int visited) {
    if (path) {
        printf("Path found! Length: %d, Visited nodes: %d\n", len, visited);
    } else {
        printf("No path found. Visited nodes: %d\n", visited);
    }
}

int main(int argc, char *argv[]) {
    int maze_size = 15;
    float density = 0.25f;
    MazePtr maze = MazeInit(maze_size, density);
    
    pair_t start = MazeGetSource(maze);
    pair_t end = MazeGetDest(maze);
    int path_len, visited;

    printf("Start: (%d,%d), Lamp: (%d,%d)\n", start.x, start.y, end.x, end.y);
    MazePrint(maze);
    pair_t *path_bfs = GraphShortestBFS(maze, start, end, &path_len, &visited);
    print_result("BFS Method", path_bfs, path_len, visited);
    if(path_bfs) MazePrintWithPath(maze, path_bfs, path_len);
    pair_t *path_dfs = GraphPathDFS(maze, start, end, &path_len, &visited);
    print_result("DFS Method", path_dfs, path_len, visited);
    printf("\n Multiple Lamps Test \n");
    char **grid = MazeGetPoints(maze);
    grid[0][0] = DEST; 
    pair_t *path_multi = FindNearestLampBFS(maze, start, &path_len, &visited);
    print_result("Nearest Lamp (Multiple)", path_multi, path_len, visited);
    if(path_multi) MazePrintWithPath(maze, path_multi, path_len);

    free(path_bfs); free(path_dfs); free(path_multi);
    MazeDestroy(maze);
    return 0;
}