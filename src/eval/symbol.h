#ifndef INCLUDE_EVAL_SYMBOL_H
#define INCLUDE_EVAL_SYMBOL_H

#define STR_EQ(STR1, STR2) strcmp(STR1, STR2) == 0

#define IF_PRIMITIVE_RETURN(PRIM, S) \
    if (STR_EQ(PRIM, S->symbol)) { \
        struct function *result_function = malloc(sizeof(struct function)); \
        result_function->type = PRIMITIVE; \
        result_function->primitive = S->symbol; \
        \
        struct sexpr *result = malloc(sizeof(struct sexpr)); \
        result->type = FUNCTION; \
        result->function = result_function; \
        \
        return result; \
    }

struct sexpr *eval_symbol(struct sexpr *s, struct map *package) {
    if (STR_EQ("NIL", s->symbol))
        return s;

    IF_PRIMITIVE_RETURN("QUOTE", s);
    IF_PRIMITIVE_RETURN("LIST", s);
    IF_PRIMITIVE_RETURN("HEAD", s);
    IF_PRIMITIVE_RETURN("TAIL", s);
    IF_PRIMITIVE_RETURN("LAMBDA", s);

    struct item *i = get(s->symbol, package);

    if (i != NULL) {
        return i->value;
    }

    return NULL;
}

#endif
