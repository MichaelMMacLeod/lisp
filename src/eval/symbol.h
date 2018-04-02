#ifndef INCLUDE_EVAL_SYMBOL_H
#define INCLUDE_EVAL_SYMBOL_H

struct sexpr *eval_symbol(struct sexpr *s, struct map *package) {
    //if (STR_EQ("NIL", s->symbol))
    //    return s;

    struct item *i = get(s->symbol, package);

    if (i != NULL) {
        if (i->value != NULL) {
            return i->value;
        } else {
            struct function *result_function = malloc(sizeof(struct function));
            result_function->type = PRIMITIVE;
            result_function->primitive = s->symbol;

            struct sexpr *result = malloc(sizeof(struct sexpr));
            result->type = FUNCTION;
            result->function = result_function;

            return result;
        }
    }

    return NULL;
}

#endif
