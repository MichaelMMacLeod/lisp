#ifndef INCLUDE_FUNCTIONS_QUOTE_H
#define INCLUDE_FUNCTIONS_QUOTE_H

struct sexpr *quote(struct list *args, struct map *package) {
    return args->head;
}

#endif
