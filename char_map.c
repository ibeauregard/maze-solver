#include "char_map.h"
#include <stdlib.h>
#include <stdio.h>

static CharMap* new();
struct char_map_class CharMapClass = {
    .new = &new
};

static void print(CharMap* self);
static void delete(CharMap* self);
CharMap* new()
{
    CharMap* self = malloc(sizeof (CharMap));

    self->print = &print;
    self->delete = &delete;
    return self;
}

void print(CharMap* self)
{
    printf("%c%c%c%c%c",
           self->wall, self->corridor, self->path, self->entrance, self->exit);
}

void delete(CharMap* self)
{
    free(self);
}
