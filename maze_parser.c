#include "maze_parser.h"
#include "my_libc/readline.h"
#include "char_map.h"
#include "maze_matrix.h"
#include "maze_internals.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

Maze* from_path(const char* path);
struct maze_parser MazeParser = {
    .fromPath = &from_path
};

typedef struct parser {
    int fd;
    CharMap* char_map;
    MazeMatrix* matrix;
} Parser;

static Parser parser;

static void parse_header();
static void fill_matrix();
static Maze* new_maze();
Maze* from_path(const char* path)
{
    parser.fd = open(path, O_RDONLY);
    parse_header();
    fill_matrix();
    close(parser.fd);
    return new_maze();
}

static char* initialize_matrix(char* header);
static void initialize_char_map(char* header);
void parse_header()
{
    char* header = readline(parser.fd);
    char* char_map = initialize_matrix(header);
    initialize_char_map(char_map);
    free(header);
}

char* initialize_matrix(char* header)
{
    long num_rows = strtol(header, &header, 10);
    long num_cols = strtol(header + 1, &header, 10);
    parser.matrix = MazeMatrixClass.new(num_rows, num_cols);
    return header;
}

void initialize_char_map(char* char_map)
{
    parser.char_map = CharMapClass.new();
    parser.char_map->wall = char_map[0];
    parser.char_map->corridor = char_map[1];
    parser.char_map->path = char_map[2];
    parser.char_map->entrance = char_map[3];
    parser.char_map->exit = char_map[4];
}

void fill_matrix()
{
    for (uint i = 0; i < parser.matrix->num_rows; i++) {
        parser.matrix->setRow(parser.matrix, i, readline(parser.fd));
    }
}

static void initialize_internals(Maze* maze);
Maze* new_maze()
{
    Maze* maze = malloc(sizeof (Maze));
    initialize_internals(maze);
    maze->valid = false;
    return maze;
}

void initialize_internals(Maze* maze)
{
    maze->_internals = malloc(sizeof (struct maze_internals));
    maze->_internals->char_map = parser.char_map;
    maze->_internals->matrix = parser.matrix;
}
