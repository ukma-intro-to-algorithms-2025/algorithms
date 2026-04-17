#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

#define OBSTACLE '#'
#define PASSAGE '.'
#define PATH '*'
#define SOURCE 'S'
#define DEST 'D'

typedef struct {
    int x;
    int y;
} pair_t;

typedef struct Maze Maze;
typedef Maze *MazePtr;

MazePtr MazeInit(int size, float obstacles);
char **MazeGetPoints(MazePtr maze);
int MazeGetSize(MazePtr maze);
pair_t MazeGetSource(MazePtr maze);
pair_t MazeGetDest(MazePtr maze);
bool MazeUpdateSourceDest(MazePtr m, pair_t source, pair_t dest);
void MazePrint(MazePtr maze);
void MazePrintWithPath(MazePtr maze, pair_t *path, int length);
void MazeDestroy(MazePtr maze);

pair_t* GraphShortestBFS(MazePtr g, pair_t start, pair_t end, int *path_len, int *visited_nodes);
pair_t* GraphPathDFS(MazePtr g, pair_t start, pair_t end, int *path_len, int *visited_nodes);
pair_t* FindNearestLampBFS(MazePtr m, pair_t start, int *path_len, int *visited_nodes);

#endif