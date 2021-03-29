#include "path_search_algo.h"
#include <stdlib.h>

static PathSearchAlgo* new(Maze* maze);
struct path_search_algo_class PathSearchAlgoClass = {
        .new = &new
};

struct path_search_algo_internals {
    Maze* maze;
};

static void run(PathSearchAlgo* self);
static void delete(PathSearchAlgo* self);
PathSearchAlgo* new(Maze* maze)
{
    PathSearchAlgo* self = malloc(sizeof (PathSearchAlgo));
    self->_internals = malloc(sizeof (struct path_search_algo_internals));
    self->_internals->maze = maze;
    self->path = MazePathClass.new();

    self->run = &run;
    self->delete = &delete;
    return self;
}

void run(PathSearchAlgo* self)
{
    self->found = false;
}

void delete(PathSearchAlgo* self)
{
    free(self->_internals);
    self->path->delete(self->path);
    free(self);
}


