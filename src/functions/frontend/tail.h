#ifndef INCLUDE_FRONTEND_TAIL_H
#define INCLUDE_FRONTEND_TAIL_H

struct sexpr *tail(struct list *args, struct map *package) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = LIST;
    result->list = eval_sexpr(args->head, package)->list->tail;

    return result;
}

#endif
