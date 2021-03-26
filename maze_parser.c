#include "maze_parser.h"

static MazeParser parser;

MazeParser* get_parser()
{
    return &parser;
}
