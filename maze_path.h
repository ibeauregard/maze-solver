#ifndef MAZE_PATH_H
#define MAZE_PATH_H

#include "maze_coords.h"

typedef struct maze_path {
    MazeCoords* (*next)(struct maze_path* self);
    void (*delete)(struct maze_path* self);
} MazePath;

struct maze_path_class {
    MazePath* (*new)();
};
extern struct maze_path_class MazePathClass;

#endif
