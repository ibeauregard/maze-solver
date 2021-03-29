#ifndef MAZE_PATH_H
#define MAZE_PATH_H

#include "maze_coords.h"
#include "maze_coords_stack.h"

struct maze_path_internals;
typedef struct maze_path {
    struct maze_path_internals* _internals;
    MazeCoords* (*next)(struct maze_path* self);
    void (*delete)(struct maze_path* self);
} MazePath;

struct maze_path_class {
    MazePath* (*new)(MazeCoordsStack* stack);
};
extern struct maze_path_class MazePathClass;

#endif
