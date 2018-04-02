#ifndef INCLUDE_FRONTEND_T_H
#define INCLUDE_FRONTEND_T_H

struct sexpr *t(struct list *args, struct map *package) {
    return eval_sexpr(args->head, package);
}

#endif
