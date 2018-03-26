#ifndef INCLUDE_EVAL_H
#define INCLUDE_EVAL_H

#include "sexpr.h"
#include "map.h"
#include "package.h"

struct sexpr *quote(struct sexpr *args) {
    return args;
}

struct sexpr *eval_sexpr(struct sexpr *form, struct map *package);

struct sexpr *eval_symbol(char *symbol, struct map *package) {
    return eval_sexpr(get_by_name(package, symbol)->binding, package);
}

struct sexpr *apply(struct sexpr *function, struct sexpr *args) {
    printf("apply is undefined\n");
    exit(1);
}

struct sexpr *eval_pair(struct pair *p, struct map *package) {
    if (p == NULL) {
        return NULL;
    }

    struct sexpr *head = eval_sexpr(p->head, package);
    struct sexpr *tail = eval_pair(p->tail, package);

    return apply(head, tail);
}

struct sexpr *eval_sexpr(struct sexpr *form, struct map *package) {
    if (form == NULL) {
        return NULL;
    }

    if (form->type == SYMBOL) {
        return eval_symbol(form->symbol, package);
    } else if (form->type == PAIR) {
        if (form->pair->head->type == SYMBOL) {
            char *function_quote = malloc(6 * sizeof(char));
            strcpy(function_quote, "QUOTE");

            if (strcmp(form->pair->head->symbol, function_quote) == 0) {
                struct sexpr *quote_tail = malloc(sizeof(struct sexpr));
                quote_tail->type = PAIR;
                quote_tail->pair = form->pair->tail;

                return quote(quote_tail);
            }
        }

        return eval_pair(form->pair, package);
    }

    printf("error: bad s-expression\n");
    exit(1);
}

#endif
