#include "path_search_algo.h"
#include <stdlib.h>

static PathSearchAlgo* new(Maze* maze);
struct path_search_algo_class PathSearchAlgoClass = {
        .new = &new
};

struct path_search_algo_internals {
    Maze* maze;
    MazeCoords* goal;
};

static void run(PathSearchAlgo* self);
static void delete(PathSearchAlgo* self);
PathSearchAlgo* new(Maze* maze)
{
    PathSearchAlgo* self = malloc(sizeof (PathSearchAlgo));
    self->_internals = malloc(sizeof (struct path_search_algo_internals));
    self->_internals->maze = maze;
    self->_internals->goal = maze->exit;

    self->run = &run;
    self->delete = &delete;
    return self;
}

void run(PathSearchAlgo* self)
{
    Maze* maze = self->_internals->maze;
    MazeCoords coords = (MazeCoords) {
        .row = 0, .col = 3
    };
    maze->walk(maze, &coords);
    coords.row = 1; maze->walk(maze, &coords);
    coords.row = 2; maze->walk(maze, &coords);
    coords.row = 3; maze->walk(maze, &coords);
    coords.col = 2; maze->walk(maze, &coords);
    coords.row = 4; maze->walk(maze, &coords);
    coords.row = 5; maze->walk(maze, &coords);
    coords.row = 6; maze->walk(maze, &coords);
    coords.row = 7; maze->walk(maze, &coords);
    coords.row = 8; maze->walk(maze, &coords);
    coords.col = 3; maze->walk(maze, &coords);
    coords.row = 9; maze->walk(maze, &coords);

    self->found = true;
}

uint minimum_remaining_cost(PathSearchAlgo* self, MazeCoords* coords)
{
    MazeCoords* goal = self->_internals->goal;
    return abs((int) (goal->row - coords->row)) + abs((int) (goal->col - coords->col));
}

bool is_goal(PathSearchAlgo* self, MazeCoords* coords)
{
    MazeCoords* goal = self->_internals->goal;
    return goal->row == coords->row && goal->col == coords->col;
}

void delete(PathSearchAlgo* self)
{
    free(self->_internals);
    free(self);
}


