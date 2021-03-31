#ifndef MAZE_PARSER_H
#define MAZE_PARSER_H

#include "maze.h"

struct maze_parser {
    Maze* (*fromPath)(const char* path);
};
extern struct maze_parser MazeParser;

#endif
