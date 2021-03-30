#ifndef ORDERED_COORDS_LIST_H
#define ORDERED_COORDS_LIST_H

#include "maze_coords.h"

struct ordered_coords_list_internals;
typedef struct ordered_coords_list {
    struct ordered_coords_list_internals* _internals;
    void (*insert)(struct ordered_coords_list* self, MazeCoords* coords, uint key);
    MazeCoords* (*pop)(struct ordered_coords_list* self);
    void (*delete)(struct ordered_coords_list* self);
} OrderedCoordsList;

struct ordered_coords_list_class {
    OrderedCoordsList* (*new)();
};
extern struct ordered_coords_list_class OrderedCoordsListClass;

#endif
