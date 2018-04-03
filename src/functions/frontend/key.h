#ifndef INCLUDE_FRONTEND_KEY_H
#define INCLUDE_FRONTEND_KEY_H

struct sexpr *key(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));

    result->type = SYMBOL;
    result->symbol = eval_sexpr(args->head, package)->item->key;

    return result;
}

#endif
