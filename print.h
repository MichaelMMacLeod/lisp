#ifndef INCLUDE_PRINT_H
#define INCLUDE_PRINT_H

#include <stdio.h>
#include "sexpr.h"

void print_symbol(char *symbol) {
    printf("%s", symbol);
}

void print_sexpr(struct sexpr *s);

void print_pair_helper(struct pair *p) {
    print_sexpr(p->head);

    if (p->tail != NULL) {
        printf(" ");

        print_pair_helper(p->tail);
    }
}

void print_pair(struct pair *p) {
    printf("(");
    print_pair_helper(p);
    printf(")");
}

void print_function(struct function *f) {
    printf("#<FUNCTION (LAMBDA ");

    print_pair(f->args);

    if (f->body != NULL) {
        printf(" ");
    }

    print_sexpr(f->body);

    printf(") ");

    printf("[%p]>", f);
}

void print_sexpr(struct sexpr *s) {
    if (s == NULL) {
        return;
    }

    if (s->type == SYMBOL) {
        print_symbol(s->symbol);
    } else if (s->type == PAIR) {
        print_pair(s->pair);
    } else if (s->type == FUNCTION) {
        print_function(s->function);
    }
}

#endif
