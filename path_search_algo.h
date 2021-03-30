#ifndef PATH_SEARCH_ALGO_H
#define PATH_SEARCH_ALGO_H

#include "maze.h"

struct path_search_algo_internals;
typedef struct path_search_algo {
    struct path_search_algo_internals* _internals;
    bool found;
    uint num_steps;
    void (*run)(struct path_search_algo* self);
    void (*delete)(struct path_search_algo* self);
} PathSearchAlgo;


struct path_search_algo_class {
    PathSearchAlgo* (*new)(Maze* maze);
};
extern struct path_search_algo_class PathSearchAlgoClass;

#endif
