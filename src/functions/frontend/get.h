#ifndef INCLUDE_FRONTEND_GET_H
#define INCLUDE_FRONTEND_GET_H

struct sexpr *get(struct list *args, struct map *package) {
    struct item *i = get_item(
            eval_sexpr(args->head, package)->symbol, 
            eval_sexpr(args->tail->head, package)->map);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = ITEM;
    result->item = i;

    return result;
}

#endif
