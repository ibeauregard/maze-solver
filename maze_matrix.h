#ifndef MAZE_MATRIX_H
#define MAZE_MATRIX_H

typedef unsigned int uint;
typedef struct maze_matrix {
    uint num_rows;
    uint num_cols;
    char** rows;

    void (*print)(struct maze_matrix* self);
    void (*delete)(struct maze_matrix* self);
} MazeMatrix;

struct maze_matrix_class {
    MazeMatrix* (*new)();
};

#endif
