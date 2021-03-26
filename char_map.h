#ifndef CHAR_MAP_H
#define CHAR_MAP_H

typedef struct char_map {
    char wall;
    char corridor;
    char path;
    char entrance;
    char exit;

    void (*print)(struct char_map* self);
    void (*delete)(struct char_map* self);
} CharMap;

struct char_map_class {
    CharMap* (*new)();
};
extern struct char_map_class CharMapClass;

#endif
