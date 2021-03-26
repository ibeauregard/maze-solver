#include "maze.h"
#include "char_map.h"
#include "maze_matrix.h"
#include <stdio.h>
#include <stdlib.h>

static Maze* from_path(const char* path);
struct maze_class MazeClass = {
    .fromPath = &from_path
};

struct maze_internals {
    CharMap* char_map;
    MazeMatrix* matrix;
};

static void initialize_internals(Maze* self);
static void print(Maze* self);
static void delete(Maze* self);
Maze* from_path(const char* path)
{
    puts(path);
    Maze* self = malloc(sizeof (Maze));
    initialize_internals(self);
    self->print = &print;
    self->delete = &delete;
    return self;
}

extern struct char_map_class CharMapClass;
extern struct maze_matrix_class MazeMatrixClass;
void initialize_internals(Maze* self)
{
    struct maze_internals* internals = malloc(sizeof (struct maze_internals));
    internals->char_map = CharMapClass.new();
    internals->matrix = MazeMatrixClass.new(10, 10);
    self->_internals = internals;
}

static void print_header(struct maze_internals* _internals);
void print(Maze* self)
{
    struct maze_internals* _internals = self->_internals;
    print_header(_internals);
    _internals->matrix->print(_internals->matrix);
}

void print_header(struct maze_internals* _internals)
{
    _internals->char_map->print(_internals->char_map);
}

static void delete_internals(struct maze_internals* _internals);
void delete(Maze* self)
{
    delete_internals(self->_internals);
    free(self);
}

void delete_internals(struct maze_internals* _internals)
{
    _internals->char_map->delete(_internals->char_map);
    _internals->matrix->delete(_internals->matrix);
    free(_internals);
}
