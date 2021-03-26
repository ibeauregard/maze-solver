#ifndef MAZE_PARSER_H
#define MAZE_PARSER_H

struct maze_parser_internals;

typedef struct maze_parser {
    struct maze_parser_internals* internals;
    void (*publicMethod)(struct maze_parser* self);
} MazeParser;

struct maze_parser_class {
    MazeParser* (*getParser)();
};
extern struct maze_parser_class MazeParserCls;

#endif
