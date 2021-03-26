#include "maze_matrix.h"
#include <stdlib.h>
#include <stdio.h>

static MazeMatrix* new();
struct maze_matrix_class MazeMatrixClass = {
    .new = &new
};

static void print(MazeMatrix* self);
static void delete(MazeMatrix* self);
MazeMatrix* new()
{
    MazeMatrix* self = malloc(sizeof (MazeMatrix));

    self->print = &print;
    self->delete = &delete;
    return self;
}

void print(MazeMatrix* self)
{
    for (uint i = 0; i < self->num_rows; i++) {
        printf("%s\n", self->rows[i]);
    }
}

void delete(MazeMatrix* self)
{
    for (uint i = 0; i < self->num_rows; i++) {
        free(self->rows[i]);
    }
    free(self);
}
