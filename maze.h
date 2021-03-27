#ifndef MAZE_H
#define MAZE_H

#include "maze_coords.h"
#include <stdbool.h>

struct maze_internals;
typedef struct maze {
    struct maze_internals* _internals;
    bool valid;
    MazeCoords* entrance;
    MazeCoords* exit;
    void (*print)(struct maze* self);
    void (*delete)(struct maze* self);
} Maze;

struct maze_class {
    Maze* (*fromPath)(const char* path);
};
extern struct maze_class MazeClass;

#endif
