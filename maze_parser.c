#include "maze_parser.h"
#include "my_libc/readline.h"
#include "char_map.h"
#include "maze_matrix.h"
#include "maze_internals.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Maze* from_path(const char* path);
struct maze_parser MazeParser = {
    .fromPath = &from_path
};

typedef struct parser {
    int fd;
    CharMap* char_map;
    MazeMatrix* matrix;
    bool failed;
    void (*init)();
} Parser;

static void init();
static Parser parser = {
    .init = &init
};

void init()
{
    parser.failed = false;
}

static void parse_header();
static void fill_matrix();
static Maze* new_maze();
Maze* from_path(const char* path)
{
    parser.init();
    if ((parser.fd = open(path, O_RDONLY)) == -1) {
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "Can't open file");
    }
    if (!parser.failed) parse_header();
    if (!parser.failed) fill_matrix();
    if (parser.fd != -1) close(parser.fd);
    return new_maze();
}

static char* initialize_matrix(char* header);
static void initialize_char_map(char* header);
void parse_header()
{
    char *header, *char_map;
    if (!(header = readline(parser.fd))){
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "File is empty");
    }
    if (!parser.failed) char_map = initialize_matrix(header);
    if (!parser.failed) initialize_char_map(char_map);
    if (header) free(header);
}

char* initialize_matrix(char* header)
{
    long num_rows, num_cols;
    if ((num_rows = strtol(header, &header, 10)) <= 0) {
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "Header specifies invalid number of rows");
    }
    if (!parser.failed && (num_cols = strtol(header + 1, &header, 10)) <= 0) {
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "Header specifies invalid number of columns");
    }
    if (!parser.failed && num_rows * num_cols > 1000000000) /* one billion */ {
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "Header specifies a number of squares greater than one billion");
    }
    if (!parser.failed) parser.matrix = MazeMatrixClass.new(num_rows, num_cols);
    return header;
}

void initialize_char_map(char* char_map)
{
    parser.char_map = CharMapClass.new();
    if (strlen(char_map) != 5) {
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "Header should specify a character mapping of length 5");
    }
    if (!parser.failed) {
        parser.char_map->wall = char_map[0];
        parser.char_map->corridor = char_map[1];
        parser.char_map->path = char_map[2];
        parser.char_map->entrance = char_map[3];
        parser.char_map->exit = char_map[4];
    }
    if (!parser.failed && !parser.char_map->hasDistinctElements(parser.char_map)) {
        parser.failed = true;
        dprintf(STDERR_FILENO, "%s\n", "Character mapping contains repeated elements");
    }
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
    maze->valid = !parser.failed;
    if (maze->valid) initialize_internals(maze);
    return maze;
}

void initialize_internals(Maze* maze)
{
    maze->_internals = malloc(sizeof (struct maze_internals));
    maze->_internals->char_map = parser.char_map;
    maze->_internals->matrix = parser.matrix;
}
