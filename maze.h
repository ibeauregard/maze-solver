#ifndef MAZE_H
#define MAZE_H

struct maze_internals;
typedef struct maze {
    struct maze_internals* _internals;
    void (*delete)(struct maze* self);
} Maze;

struct maze_class {
    Maze* (*fromPath)(const char* path);
};
extern struct maze_class MazeClass;

#endif
