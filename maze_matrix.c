#include "maze_matrix.h"
#include <stdlib.h>
#include <stdio.h>

static MazeMatrix* new();
struct maze_matrix_class MazeMatrixClass = {
    .new = &new
};

static void print(MazeMatrix* self);
static void delete(MazeMatrix* self);
MazeMatrix* new(uint num_rows, uint num_cols)
{
    MazeMatrix* self = malloc(sizeof (MazeMatrix));
    self->num_rows = num_rows;
    self->num_cols = num_cols;
    self->rows = malloc(self->num_rows * sizeof (char*));
    for (uint i = 0; i < self->num_rows; i++) {
        self->rows[i] = malloc(self->num_cols + 1);
        self->rows[i][self->num_cols] = 0;
    }


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
    free(self->rows);
    free(self);
}
