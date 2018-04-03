#ifndef INCLUDE_FRONTEND_NIL_H
#define INCLUDE_FRONTEND_NIL_H

struct sexpr *nil(struct list *args, struct map *package) {
    if (args->tail != NULL) {
        return eval_sexpr(args->tail->head, package);
    }

    return NULL;
}

#endif
