#ifndef INCLUDE_PACKAGE_H
#define INCLUDE_PACKAGE_H

#include "map.h"

char upper_case(char c) {
    if (c >= 97 && c <= 122) {
        return c - 32;
    } else {
        return c;
    }
}

// intern - add a symbol to a package.
//
// If the symbol is already interned in the package the new one is not added,
// and the existing one is returned.
struct map_item *intern(struct map_item *item, struct map *package) {
    char *c = item->name;

    while (*c != '\0') {
        *c = upper_case(*c);

        ++c;
    }

    struct map_item *interned_item = get(package, item);

    if (interned_item == NULL) {
        interned_item = item;
        add(package, interned_item);
    }

    return interned_item;
}

//struct map_item *package_get_by_name(

struct map_item *create_item_nil() {
    char *str_nil = malloc(4 * sizeof(char));
    strcpy(str_nil, "nil");

    struct map_item *item_nil = malloc(sizeof(struct map_item));
    item_nil->name = str_nil;
    item_nil->binding = NULL;

    return item_nil;
}

struct map *create_default_package() {
    struct map *package = malloc(sizeof(struct map));
    package->size = 0;
    package->items = malloc(0);

    intern(create_item_nil(), package);

    return package;
}

#endif
