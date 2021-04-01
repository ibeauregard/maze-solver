#ifndef PATH_SEARCH_ALGO_H
#define PATH_SEARCH_ALGO_H

#include "maze.h"

typedef struct path_search_algo PathSearchAlgo;
struct path_search_algo_internals;
struct path_search_algo {
    struct path_search_algo_internals* _internals;
    bool found;
    uint num_steps;
    void (*run)(PathSearchAlgo* self);
    void (*delete)(PathSearchAlgo* self);
};


struct path_search_algo_class {
    PathSearchAlgo* (*new)(Maze* maze);
} PathSearchAlgoClass;

#endif
