#include "maze_solver.h"
#include "path_search_algo.h"
#include <stdio.h>
#include <unistd.h>

static void solve(Maze* maze);
struct maze_solver MazeSolver = {
    .solve = &solve
};

void solve(Maze* maze)
{
    PathSearchAlgo* algo = PathSearchAlgoClass.new(maze);
    algo->run(algo);
    if (!algo->found) dprintf(STDERR_FILENO, "%s\n", "Maze has no solution");
    maze->print(maze);
    if (algo->found) printf("%u STEPS!\n", algo->num_steps);
    algo->delete(algo);
    puts("");
}
