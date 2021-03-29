#include "maze_solver.h"
#include <stdio.h>

static void solve(Maze* maze);
struct maze_solver_class MazeSolverClass = {
    .solve = &solve
};

void solve(Maze* maze)
{
    if (maze->valid) {
        return;
    } else {
        return;
    }
}
