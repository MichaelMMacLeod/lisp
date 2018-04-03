#ifndef INCLUDE_FRONTEND_PRINT_H
#define INCLUDE_FRONTEND_PRINT_H

struct sexpr *print(struct list *args, struct map *package) {
    struct sexpr *s = eval_sexpr(args->head, package);

    print_sexpr(s);

    return s;
}

#endif
