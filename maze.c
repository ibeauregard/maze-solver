#include "maze.h"
#include "char_map.h"
#include "maze_matrix.h"
#include "maze_parser.h"
#include "maze_internals.h"
#include <stdio.h>
#include <stdlib.h>

static Maze* from_path(const char* path);
struct maze_class MazeClass = {
    .fromPath = &from_path
};

static void print(Maze* self);
static void delete(Maze* self);
Maze* from_path(const char* path)
{
    Maze* self = MazeParser.fromPath(path);
    self->print = &print;
    self->delete = &delete;
    return self;
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
    printf("%dx%d", _internals->matrix->num_rows, _internals->matrix->num_cols);
    _internals->char_map->print(_internals->char_map);
    puts("");
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
