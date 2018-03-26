#ifndef INCLUDE_EVAL_H
#define INCLUDE_EVAL_H

#include "sexpr.h"
#include "map.h"
#include "package.h"

int quote_p(struct sexpr *form) {
    char *nil_str = "QUOTE";

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(nil_str, form->pair->head->symbol) == 0;
    }

    printf("quote_p - undefined form type");
    exit(1);
}

struct sexpr *interpret_quote(struct pair *arg) {
    return arg->head;
}

struct sexpr *eval_sexpr(struct sexpr *form) {
    if (quote_p(form)) {
        return interpret_quote(form->pair->tail);
    }

    printf("eval_sexpr - undefined form\n");
    exit(1);
}

#endif
