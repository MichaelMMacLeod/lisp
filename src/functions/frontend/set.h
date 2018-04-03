#ifndef INCLUDE_FRONTEND_SET_H
#define INCLUDE_FRONTEND_SET_H

struct sexpr *set(struct list *args, struct map *package) {
    struct item *i = eval_sexpr(args->head, package)->item;

    i->value = malloc(sizeof(struct sexpr));
    *i->value = *eval_sexpr(args->tail->head, package);

    add(i, eval_sexpr(args->head->list->tail->tail->head, package)->map);

    return i->value;
}

#endif
