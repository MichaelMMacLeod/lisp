#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

struct sexpr *eval_symbol(char *symbol, struct map *m);
struct pair *eval_pair(struct pair *p, struct map *m);
struct sexpr *eval_sexpr(struct sexpr *form, struct map *m);
struct item *add(struct item *i, struct map *m);

///////////////////////////////////////////////////////////////////////////////
// utilities
///////////////////////////////////////////////////////////////////////////////

// create_item - create an item with a key and value
//
// return - the new item
struct item *create_item(char *key, struct sexpr *value) {
    struct item *result = malloc(sizeof(struct item));

    result->key = key;
    result->value = value;

    return result;
}

// create_empty_map - create a map of size zero
// 
// return - the empty map
struct map *create_empty_map() {
    struct map *result = malloc(sizeof(struct map));

    result->size = 0;
    result->items = NULL;

    return result;
}

int exists(struct item *i, struct map *m) {
    for (int k = 0; k < m->size; ++k) {
        if (strcmp(i->key, m->items[k].key) == 0) {
            return 1;
        }
    }

    return 0;
}

// get - return the item in a map with a key lexicographically equal to the one
// provided
//
// return - the item, or a new one with a NULL value if it doesn't exist in the
// map
struct item *get(char *key, struct map *m) {
    for (int k = 0; k < m->size; ++k) {
        if (strcmp(key, m->items[k].key) == 0) {
            return &m->items[k];
        }
    }

    struct item *i = malloc(sizeof(struct item));

    i->key = key;
    i->value = NULL;

    return i;
}

// add_non_shadowing - add an item to a map but don't shadow a duplicate if it
// exists
//
// return - the new item, or, if it was a duplicate, the original
struct item *add_without_shadowing(struct item *i, struct map *m) {
    struct item *possible_duplicate = get(i->key, m);

    if (!exists(possible_duplicate, m)) {
        ++m->size;

        m->items = realloc(m->items, m->size * sizeof(struct item));
        m->items[m->size - 1] = *i;

        return i;
    } else {
        return possible_duplicate;
    }
}

// add - add an item to a map and shadow a duplicate if it exists
//
// return - the new item
struct item *add(struct item *i, struct map *m) {
    struct item *possible_duplicate = get(i->key, m);

    if (!exists(possible_duplicate, m)) {
        ++m->size;

        m->items = realloc(m->items, m->size * sizeof(struct item));
        m->items[m->size - 1] = *i;

        return i;
    } else {
        possible_duplicate->value = i->value;

        return possible_duplicate;
    }
}

// remove_item - remove an item from a map
//
// return - the removed item, NULL if it didn't exist in the map
struct item *remove_item(struct item *i, struct map *m) {
    for (int j = 0; j < m->size; ++j) {
        if (strcmp(m->items[j].key, i->key) == 0) {
            struct item *removed = &m->items[j];
            struct item *result = create_item(removed->key, removed->value);

            for (int k = j; k < m->size - 1; ++k) {
                m->items[k] = m->items[k + 1];
            }

            --m->size;

            return result;
        }
    }

    return NULL;
}

// copy - shallow copy a map
//
// return - the copy, which retains the same underlying key and value pointers
struct map *copy(struct map *m) {
    struct map *copy = create_empty_map();

    for (int i = 0; i < m->size; ++i) {
        struct item *item_copy = malloc(sizeof(struct item));

        item_copy->key = m->items[i].key;
        item_copy->value = m->items[i].value;

        add(item_copy, copy);
    }

    return copy;
}

///////////////////////////////////////////////////////////////////////////////
// eval-time
///////////////////////////////////////////////////////////////////////////////

struct sexpr *interpret_create_map(struct pair *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = MAP;
    result->map = create_empty_map();

    return result;
}

struct sexpr *interpret_set(struct pair *args, struct map *package) {
    struct item *new_item = malloc(sizeof(struct item));
    new_item->key = eval_sexpr(args->head, package)->item->key;
    new_item->value = eval_sexpr(args->tail->head, package);

    return add(new_item, eval_sexpr(args->tail->tail->head, package)->map)->value;
}

#endif
