#include "path_search_algo.h"
#include "coords_iterator.h"
#include <stdlib.h>
#include <limits.h>

static PathSearchAlgo* new(Maze* maze);
struct path_search_algo_class PathSearchAlgoClass = {
        .new = &new
};

struct path_search_algo_internals {
    Maze* maze;
    MazeCoords* goal;
};

static void run(PathSearchAlgo* self);
static void delete(PathSearchAlgo* self);
PathSearchAlgo* new(Maze* maze)
{
    PathSearchAlgo* self = malloc(sizeof (PathSearchAlgo));
    self->_internals = malloc(sizeof (struct path_search_algo_internals));
    self->_internals->maze = maze;
    self->_internals->goal = maze->exit;
    self->found = false;

    self->run = &run;
    self->delete = &delete;
    return self;
}

static uint min_remaining_cost(PathSearchAlgo* self, MazeCoords* coords);
static uint search(PathSearchAlgo* self, MazeCoords* coords, uint current_cost);
void run(PathSearchAlgo* self)
{
    self->num_steps = min_remaining_cost(self, self->_internals->maze->entrance);
    uint t;
    while (true) {
        t = search(self, self->_internals->maze->entrance, 0);
        if (self->found || t == UINT_MAX) return;
        self->num_steps = t;
    }
}

uint min_remaining_cost(PathSearchAlgo* self, MazeCoords* coords)
{
    MazeCoords* goal = self->_internals->goal;
    return abs((int) (goal->row - coords->row)) + abs((int) (goal->col - coords->col));
}

static bool is_goal(PathSearchAlgo* self, MazeCoords* coords);
static CoordsIterator* ordered_neighbors_of(PathSearchAlgo* self, MazeCoords* coords);
uint search(PathSearchAlgo* self, MazeCoords* coords, uint current_cost)
{
    uint f = current_cost + min_remaining_cost(self, coords);
    if (f > self->num_steps) return f;
    if (is_goal(self, coords)) {
        self->found = true;
        return f;
    }
    uint min = UINT_MAX, t;
    Maze* maze = self->_internals->maze;
    MazeCoords* next;
    CoordsIterator* orderedNeighbors = ordered_neighbors_of(self, coords);
    while ((next = orderedNeighbors->next(orderedNeighbors))) {
        maze->walk(maze, next);
        t = search(self, next, current_cost + 1);
        if (self->found) return t;
        if (t < min) min = t;
        maze->walkBack(maze, next);
        next->delete(next);
    }
    orderedNeighbors->delete(orderedNeighbors);
    return min;
}

bool is_goal(PathSearchAlgo* self, MazeCoords* coords)
{
    MazeCoords* goal = self->_internals->goal;
    return goal->row == coords->row && goal->col == coords->col;
}

static signed char directions[][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
static unsigned char num_directions = 4;

CoordsIterator* ordered_neighbors_of(PathSearchAlgo* self, MazeCoords* coords)
{
    OrderedCoordsList* list = OrderedCoordsListClass.new();
    Maze* maze = self->_internals->maze;
    uint row, col;
    for (unsigned char i = 0; i < num_directions; i++) {
        row = coords->row + directions[i][0];
        col = coords->col + directions[i][1];
        if (maze->isCorridorOrExit(maze, &(MazeCoords) {.row = row,
                                                  .col = col})) {
            MazeCoords* insertedCoords = MazeCoordsClass.new(row, col);
            list->insert(list, insertedCoords, min_remaining_cost(self, insertedCoords));
        }
    }
    return CoordsIteratorClass.new(list);
}

void delete(PathSearchAlgo* self)
{
    free(self->_internals);
    free(self);
}
