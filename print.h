#ifndef INCLUDE_PRINT_H
#define INCLUDE_PRINT_H

#include <stdio.h>
#include "sexpr.h"

void print_symbol(char *symbol) {
    printf("%s", symbol);
}

void print_sexpr(struct sexpr *s);

void print_pair(struct pair *p) {
    print_sexpr(p->head);

    if (p->tail != NULL) {
        printf(" ");

        print_pair(p->tail);
    }
}

void print_sexpr(struct sexpr *s) {
    if (s->type == SYMBOL) {
        print_symbol(s->symbol);
    } else if (s->type == PAIR) {
        printf("(");
        print_pair(s->pair);
        printf(")");
    }
}

#endif
