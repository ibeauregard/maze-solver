#include "maze_path.h"
#include <stdlib.h>

static MazePath* new(MazeCoordsStack* stack);
struct maze_path_class MazePathClass = {
        .new = &new
};

struct maze_path_internals {
    MazeCoordsStack* stack;
};

static MazeCoords* next(MazePath* self);
static void delete(MazePath* self);
MazePath* new(MazeCoordsStack* stack)
{
    MazePath* self = malloc(sizeof (MazePath));
    self->_internals = malloc(sizeof (struct maze_path_internals));
    self->_internals->stack = stack;
    self->next = &next;
    self->delete = &delete;
    return self;
}

MazeCoords* next(MazePath* self)
{
    return self->_internals->stack->pop(self->_internals->stack);
}

void delete(MazePath* self)
{
    self->_internals->stack->delete(self->_internals->stack);
    free(self->_internals);
    free(self); self = NULL;
}

