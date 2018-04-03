#ifndef INCLUDE_FRONTEND_PRINT_H
#define INCLUDE_FRONTEND_PRINT_H

struct sexpr *print(struct list *args, struct map *package) {
    print_sexpr(args->head);

    return args->head;
}

#endif
