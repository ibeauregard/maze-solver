#ifndef MAZE_MATRIX_H
#define MAZE_MATRIX_H

#include "maze_coords.h"

typedef unsigned int uint;
typedef struct maze_matrix {
    uint num_rows;
    uint num_cols;
    char** rows;

    void (*setElement)(struct maze_matrix* self, MazeCoords* coords, char value);
    void (*setRow)(struct maze_matrix* self, uint index, char* content);
    void (*print)(struct maze_matrix* self);
    void (*delete)(struct maze_matrix* self);
} MazeMatrix;

struct maze_matrix_class {
    MazeMatrix* (*new)(uint num_rows, uint num_cols);
};
extern struct maze_matrix_class MazeMatrixClass;

#endif
