#ifndef INCLUDE_FRONTEND_CREATE_MAP_H
#define INCLUDE_FRONTEND_CREATE_MAP_H

struct sexpr *create_map(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = MAP;
    result->map = create_empty_map();

    return result;
}

#endif
