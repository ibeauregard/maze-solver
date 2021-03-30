#ifndef COORDS_ITERATOR_H
#define COORDS_ITERATOR_H

#include "maze_coords.h"
#include "ordered_coords_list.h"

struct coords_iterator_internals;
typedef struct coords_iterator {
    struct coords_iterator_internals* _internals;
    MazeCoords* (*next)(struct coords_iterator* self);
    void (*delete)(struct coords_iterator* self);
} CoordsIterator;

struct coords_iterator_class {
    CoordsIterator* (*new)(OrderedCoordsList* list);
};
extern struct coords_iterator_class CoordsIteratorClass;

#endif
