#include "maze.h"
#include "char_map.h"
#include "maze_matrix.h"
#include <stdio.h>
#include <string.h>
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
static void initialize_char_map(struct maze_internals* _internals);
static void initialize_matrix(struct maze_internals* _internals);
void initialize_internals(Maze* self)
{
    self->_internals = malloc(sizeof (struct maze_internals));
    initialize_char_map(self->_internals);
    initialize_matrix(self->_internals);
}

void initialize_char_map(struct maze_internals* _internals)
{
    _internals->char_map = CharMapClass.new();
    _internals->char_map->wall = '*';
    _internals->char_map->corridor = ' ';
    _internals->char_map->path = 'o';
    _internals->char_map->entrance = '1';
    _internals->char_map->exit = '2';
}

void initialize_matrix(struct maze_internals* _internals)
{
    _internals->matrix = MazeMatrixClass.new(10, 10);
    for (uint i = 0; i < _internals->matrix->num_rows; i++) {
        _internals->matrix->setRow(_internals->matrix, i, strdup("** *  * **"));
    }

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
