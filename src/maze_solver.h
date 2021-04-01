#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "maze.h"

struct maze_solver {
    void (*solve)(const char* path);
} MazeSolver;

#endif
