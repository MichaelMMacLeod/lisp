#ifndef INCLUDE_APPLY_FUNCTION_H
#define INCLUDE_APPLY_FUNCTION_H

#include "primitive.h"
#include "lambda.h"

struct sexpr *apply_function(struct function *fn, struct list *args, struct map *package) {
    if (fn->type == PRIMITIVE)
        return apply_primitive(fn->primitive, args, package);

    if (fn->type == LAMBDA)
        return apply_lambda(fn->lambda, args, package);

    return NULL;
}

#endif
