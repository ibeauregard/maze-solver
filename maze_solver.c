#include "maze_solver.h"
#include "path_search_algo.h"
#include <stdio.h>
#include <unistd.h>

static void solve(Maze* maze);
struct maze_solver_class MazeSolverClass = {
    .solve = &solve
};

void solve(Maze* maze)
{
    PathSearchAlgo* algo = PathSearchAlgoClass.new(maze);
    algo->run(algo);
    if (algo->found) {
        maze->tracePath(maze, algo->path);
    } else {
        dprintf(STDERR_FILENO, "%s\n", "Maze has no solution");
    }
    algo->delete(algo);
}
