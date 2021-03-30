#include "coords_iterator.h"
#include <stdlib.h>

static CoordsIterator* new(OrderedCoordsList* list);
struct coords_iterator_class CoordsIteratorClass = {
        .new = &new
};

struct coords_iterator_internals {
    OrderedCoordsList* list;
};
static MazeCoords* next(CoordsIterator* self);
static void delete(CoordsIterator* self);
CoordsIterator* new(OrderedCoordsList* list)
{
    CoordsIterator* self = malloc(sizeof (CoordsIterator));
    self->_internals = malloc(sizeof (struct coords_iterator_internals));
    self->_internals->list = list;

    self->next = &next;
    self->delete = &delete;
    return self;
}

MazeCoords* next(CoordsIterator* self)
{
    return self->_internals->list->pop(self->_internals->list);
}

void delete(CoordsIterator* self)
{
    MazeCoords* next;
    while ((next = self->next(self))) {
        next->delete(next);
    }
    self->_internals->list->delete(self->_internals->list);
    free(self->_internals);
    free(self); self = NULL;
}
