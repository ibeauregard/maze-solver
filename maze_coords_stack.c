#include "maze_coords_stack.h"
#include <stdlib.h>

static MazeCoordsStack* new();
struct maze_coords_stack_class MazeCoordsStackClass = {
        .new = &new
};

static void initialize_internals(MazeCoordsStack* self);
static void push(MazeCoordsStack* self, MazeCoords* coords);
static MazeCoords* pop(MazeCoordsStack* self);
static MazeCoords* peek(MazeCoordsStack* self);
static void delete(MazeCoordsStack* self);
MazeCoordsStack* new()
{
    MazeCoordsStack* self = malloc(sizeof (MazeCoordsStack));
    initialize_internals(self);
    self->push = &push;
    self->pop = &pop;
    self->peek = &peek;
    self->delete = &delete;
    return self;
}

typedef struct maze_coords_node {
    MazeCoords* coords;
    struct maze_coords_node* next;
    void (*delete)(struct maze_coords_node* self);
} MazeCoordsNode;

struct maze_coords_stack_internals {
    MazeCoordsNode* top;
};

void initialize_internals(MazeCoordsStack* self)
{
    self->_internals = malloc(sizeof (struct maze_coords_stack_internals));
    self->_internals->top = NULL;
}

static MazeCoordsNode* new_maze_coords_node(MazeCoords* coords);
void push(MazeCoordsStack* self, MazeCoords* coords)
{
    MazeCoordsNode* node = new_maze_coords_node(coords);
    node->next = self->_internals->top;
    self->_internals->top = node;
}

static void delete_node(MazeCoordsNode* self);
MazeCoordsNode* new_maze_coords_node(MazeCoords* coords)
{
    MazeCoordsNode* self = malloc(sizeof (MazeCoordsNode));
    self->coords = coords;
    self->next = NULL;
    self->delete = &delete_node;
    return self;
}

void delete_node(MazeCoordsNode* self)
{
    free(self); self = NULL;
}

MazeCoords* pop(MazeCoordsStack* self)
{
    MazeCoordsNode* top = self->_internals->top;
    if (!top) return NULL;
    MazeCoords* popped = top->coords;
    MazeCoordsNode* new_top = top->next;
    top->delete(top);
    self->_internals->top = new_top;
    return popped;
}

MazeCoords* peek(MazeCoordsStack* self)
{
    return self->_internals->top ? self->_internals->top->coords : NULL;
}

void delete(MazeCoordsStack* self)
{
    struct maze_coords_stack_internals* _internals = self->_internals;
    while (_internals->top) {
        MazeCoordsNode* next = _internals->top->next;
        _internals->top->coords->delete(_internals->top->coords);
        _internals->top->delete(_internals->top);
        _internals->top = next;
    }
    free(self->_internals);
    free(self); self = NULL;
}
