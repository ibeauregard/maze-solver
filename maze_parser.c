#include "maze_parser.h"

MazeParser* get_parser();
struct maze_parser_class MazeParserCls = {
    .getParser = &get_parser
};

static MazeParser parser;

MazeParser* get_parser()
{
    return &parser;
}
