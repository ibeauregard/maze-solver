#ifndef CHAR_MAP_H
#define CHAR_MAP_H

#include <stdbool.h>

typedef struct char_map {
    char wall;
    char corridor;
    char path;
    char entrance;
    char exit;

    bool (*hasDistinctElements)(struct char_map* self);
    void (*print)(struct char_map* self);
    void (*delete)(struct char_map* self);
} CharMap;

struct char_map_class {
    CharMap* (*new)();
};
extern struct char_map_class CharMapClass;

#endif
