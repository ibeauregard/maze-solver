#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "maze.h"

struct maze_solver_class {
    void (*solve)(Maze* maze);
};
extern struct maze_solver_class MazeSolverClass;

#endif
