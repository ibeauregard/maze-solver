#include "maze_path.h"
#include <stdlib.h>

static MazePath* new();
struct maze_path_class MazePathClass = {
        .new = &new
};

static void delete(MazePath* self);
MazePath* new()
{
    MazePath* self = malloc(sizeof (MazePath));
    self->delete = &delete;
    return self;
}

void delete(MazePath* self)
{
    free(self);
}

