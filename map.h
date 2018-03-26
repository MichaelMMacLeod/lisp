#ifndef INCLUDE_MAP_H 
#define INCLUDE_MAP_H

#include <stdlib.h>
#include <string.h>
#include "sexpr.h"

struct map_item {
    char *name;
    struct sexpr *binding;
};

struct map {
    int size;
    struct map_item *items;
};

int item_equal(struct map_item *a, struct map_item *b) {
    return strcmp(a->name, b->name) == 0;
}

void add(struct map *m, struct map_item *item) {
    ++m->size;

    m->items = realloc(m->items, m->size * sizeof(struct map_item));

    m->items[m->size - 1] = *item;
}

struct map_item *get(struct map *m, struct map_item *item) {
    struct map_item *curr = m->items;

    for (int i = 0; i < m->size; ++i) {
        if (item_equal(curr, item)) {
            return curr;
        }

        ++curr;
    }

    return NULL;
}

struct map_item *get_by_name(struct map *m, char *item_name) {
    struct map_item *item = malloc(sizeof(struct map_item));
    item->name = item_name;

    struct map_item *result = get(m, item);

    free(item);

    return result;
}

#endif
