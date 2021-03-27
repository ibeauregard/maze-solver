#ifndef MAZE_COORDS_H
#define MAZE_COORDS_H

typedef unsigned int uint;

typedef struct maze_coords {
    uint row;
    uint col;
    void (*delete)(struct maze_coords* self);
} MazeCoords;

struct maze_coords_class {
    MazeCoords* (*new)(uint row, uint col);
};
extern struct maze_coords_class MazeCoordsClass;

#endif
