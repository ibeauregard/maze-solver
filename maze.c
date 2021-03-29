#include "maze.h"
#include "char_map.h"
#include "maze_matrix.h"
#include "maze_parser.h"
#include "maze_internals.h"
#include <stdio.h>
#include <stdlib.h>

#define INVALID_MAP_ERR "MAP ERROR"

static Maze* from_path(const char* path);
struct maze_class MazeClass = {
    .fromPath = &from_path
};

static void trace_path(Maze* self, MazePath* path);
static void print(Maze* self);
static void delete(Maze* self);
Maze* from_path(const char* path)
{
    Maze* self = MazeParser.fromPath(path);
    self->tracePath = &trace_path;
    self->print = &print;
    self->delete = &delete;
    return self;
}

void trace_path(Maze* self, MazePath* path)
{
    char path_char = self->_internals->char_map->entrance;
    MazeMatrix* matrix = self->_internals->matrix;
    MazeCoords* coords;
    while ((coords = path->next(path))) {
        matrix->setElement(matrix, coords, path_char);
    }
}

static void print_error_message();
static void print_header(struct maze_internals* _internals);
void print(Maze* self)
{
    if (!self->valid) {
        print_error_message();
        return;
    }
    struct maze_internals* _internals = self->_internals;
    print_header(_internals);
    _internals->matrix->print(_internals->matrix);
}

void print_error_message()
{
    puts(INVALID_MAP_ERR);
}

void print_header(struct maze_internals* _internals)
{
    printf("%ux%u", _internals->matrix->num_rows, _internals->matrix->num_cols);
    _internals->char_map->print(_internals->char_map);
    puts("");
}

static void delete_internals(struct maze_internals* _internals);
void delete(Maze* self)
{
    if (self->valid) {
        delete_internals(self->_internals);
        self->entrance->delete(self->entrance);
        self->exit->delete(self->exit);
    }
    free(self);
}

void delete_internals(struct maze_internals* _internals)
{
    _internals->char_map->delete(_internals->char_map);
    _internals->matrix->delete(_internals->matrix);
    free(_internals);
}
