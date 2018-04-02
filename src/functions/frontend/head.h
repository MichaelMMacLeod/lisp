#ifndef INCLUDE_FUNCTIONS_HEAD_H
#define INCLUDE_FUNCTIONS_HEAD_H

struct sexpr *head(struct list *args, struct map *package) {
    return eval_sexpr(args->head, package)->list->head;
}

#endif
