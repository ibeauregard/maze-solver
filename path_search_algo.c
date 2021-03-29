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
    self->path = NULL;

    self->run = &run;
    self->delete = &delete;
    return self;
}

void run(PathSearchAlgo* self)
{
    MazeCoordsStack* stack = MazeCoordsStackClass.new();
    stack->push(stack, MazeCoordsClass.new(1, 3));
    stack->push(stack, MazeCoordsClass.new(2, 3));
    stack->push(stack, MazeCoordsClass.new(3, 3));
    stack->push(stack, MazeCoordsClass.new(3, 2));
    stack->push(stack, MazeCoordsClass.new(4, 2));
    stack->push(stack, MazeCoordsClass.new(5, 2));
    stack->push(stack, MazeCoordsClass.new(6, 2));
    stack->push(stack, MazeCoordsClass.new(7, 2));
    stack->push(stack, MazeCoordsClass.new(8, 2));
    stack->push(stack, MazeCoordsClass.new(8, 3));

    self->path = MazePathClass.new(stack);
    self->found = true;
}

void delete(PathSearchAlgo* self)
{
    free(self->_internals);
    self->path->delete(self->path);
    free(self);
}


