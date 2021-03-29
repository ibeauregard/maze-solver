#ifndef MAZE_COORDS_STACK_H
#define MAZE_COORDS_STACK_H

#include "maze_coords.h"

struct maze_coords_stack_internals;
typedef struct maze_coords_stack {
    struct maze_coords_stack_internals* _internals;
    void (*push)(struct maze_coords_stack* self, MazeCoords* coords);
    MazeCoords* (*pop)(struct maze_coords_stack* self);
    void (*delete)(struct maze_coords_stack* self);
} MazeCoordsStack;

struct maze_coords_stack_class {
    MazeCoordsStack* (*new)();
};
extern struct maze_coords_stack_class MazeCoordsStackClass;

#endif
