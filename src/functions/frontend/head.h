#ifndef INCLUDE_FRONTEND_HEAD_H
#define INCLUDE_FRONTEND_HEAD_H

struct sexpr *head(struct list *args, struct map *package) {
    return eval_sexpr(args->head, package)->list->head;
}

#endif
