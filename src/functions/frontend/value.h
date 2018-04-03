#ifndef INCLUDE_FRONTEND_VALUE_H
#define INCLUDE_FRONTEND_VALUE_H

struct sexpr *value(struct list *args, struct map *package) {
    return eval_sexpr(args->head, package)->item->value;
}

#endif
