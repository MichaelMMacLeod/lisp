#ifndef INCLUDE_FRONTEND_NIL_H
#define INCLUDE_FRONTEND_NIL_H

struct sexpr *nil(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = get("NIL", package)->key;

    return result;
}

#endif
