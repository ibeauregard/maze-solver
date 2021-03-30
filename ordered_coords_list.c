#include "ordered_coords_list.h"
#include <stdlib.h>

static OrderedCoordsList* new();
struct ordered_coords_list_class OrderedCoordsListClass = {
        .new = &new
};

typedef struct ordered_coords_node OrderedCoordsNode;
struct ordered_coords_list_internals {
    OrderedCoordsNode* head;
};

static void insert(OrderedCoordsList* self, MazeCoords* coords, uint key);
static MazeCoords* pop(OrderedCoordsList* self);
static void delete(OrderedCoordsList* self);
OrderedCoordsList* new()
{
    OrderedCoordsList* self = malloc(sizeof (OrderedCoordsList));
    self->_internals = malloc(sizeof (struct ordered_coords_list_internals));
    self->_internals->head = NULL;

    self->insert = &insert;
    self->pop = &pop;
    self->delete = &delete;
    return self;
}

struct ordered_coords_node {
    MazeCoords* coords;
    uint key;
    OrderedCoordsNode* next;
};
void insert(OrderedCoordsList* self, MazeCoords* coords, uint key)
{
    OrderedCoordsNode* inserted = malloc(sizeof (OrderedCoordsNode));
    inserted->coords = coords; inserted->key = key;
    OrderedCoordsNode* node = self->_internals->head;
    if (!node || key <= node->key) {
        self->_internals->head = inserted;
        inserted->next = node;
        return;
    }
    while (node->next && node->next->key > key) {
        node = node->next;
    }
    inserted->next = node->next;
    node->next = inserted;
}

MazeCoords* pop(OrderedCoordsList* self)
{
    OrderedCoordsNode* head = self->_internals->head;
    if (!head) return NULL;
    MazeCoords* popped = head->coords;
    self->_internals->head = head->next;
    free(head);
    return popped;
}

void delete(OrderedCoordsList* self)
{
    free(self->_internals);
    free(self); self = NULL;
}
