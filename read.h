#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

#include <string.h>
#include "sexpr.h"
#include "env.h"

// copy_head_str - create a '\0' delimited string out of the next valid
// sexpr.
//
// The result points to a copy of a portion of the input.
char *copy_head_str(char *input) {
    char *p = input;

    int size = 0;

    int n_open = 0;

    while (1) {
        if ((*p == ' ' || *p == ')' || *p == '\0') && n_open == 0) {
            break;
        }

        if (*p == '(') {
            ++n_open;
        } else if (*p == ')') {
            --n_open;
        }

        ++size;
        ++p;
    }

    char *result = malloc(size * sizeof(char));
    char *r = result;

    p = input;

    for (int i = 0; i < size; ++i) {
        *r = *p;
        
        ++r;
        ++p;
    }

    *r = '\0';

    return result;
}

// upcase - convert a '\0'-delimited string to full uppercase.
void upcase(char *symbol) {
    char *curr = symbol;

    while (*curr != '\0') {
        if (*curr >= 97 && *curr <= 122) {
            *curr -= 32;
        }

        ++curr;
    }
}

// read_symbol - read a '\0'-delimited string and add a null binding to the
// environment.
struct sexpr *read_symbol(char *input, struct env *e) {
    char *symbol = copy_head_str(input);
    upcase(symbol);

    struct binding *b = add_null_binding(symbol, e);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = b->symbol;

    return result;
}

// cons - construct a linked list.
struct pair *cons(struct sexpr *head, struct pair *tail) {
    struct pair *result = malloc(sizeof(struct pair));

    result->head = head;
    result->tail = tail;

    return result;
}

// tail_str - the tail of the current pair string.
//
// The result is part of the same input string - not a copy.
//
// The result is the location of the ' ' or ')' following the first sexpr,
// meaning that to read the second sexpr, you need to disregard any spaces.
char *tail_str(char *input) {
    int n_open = 0;

    while (1) {
        if ((*input == ' ' || *input == ')') && n_open == 0) {
            break;
        }

        if (*input == '(') {
            ++n_open;
        } else if (*input == ')') {
            --n_open;
        }

        ++input;
    }

    return input;
}

struct sexpr *read_sexpr(char *input, struct env *environment);

// read_pair - read a linked list from a string until the ending ')'.
//
// The beginning '(' should NOT be included when calling read_pair.
struct sexpr *read_pair(char *input, struct env *environment) {
    while (*input == ' ') {
        ++input;
    }

    if (*input == ')') {
        return NULL;
    }

    char *head_str = copy_head_str(input);
    struct sexpr *head = read_sexpr(head_str, environment);

    char *tail_str_pos = tail_str(input);
    struct sexpr *tail = read_pair(tail_str_pos, environment);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;

    if (tail == NULL) {
        result->pair = cons(head, NULL);
    } else {
        result->pair = cons(head, tail->pair);
    }

    return result;
}

// read_quoted - reader macro which maps 'symbol to (quote symbol)
struct sexpr *read_quotted(char *input, struct env *environment) {
    char *quote_str = malloc(7 * sizeof(char));
    strcpy(quote_str, "QUOTE");

    struct sexpr *quotted_sexpr = malloc(sizeof(struct sexpr));
    quotted_sexpr->type = SYMBOL;
    quotted_sexpr->symbol = quote_str;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;

    result->pair = malloc(sizeof(struct pair));

    struct pair *quotted_pair = malloc(sizeof(struct pair));
    quotted_pair->head = read_sexpr(input, environment);
    quotted_pair->tail = NULL;

    result->pair->head = quotted_sexpr;
    result->pair->tail = quotted_pair;

    return result;
}

// read_sexpr - read an s-expression.
struct sexpr *read_sexpr(char *input, struct env *environment) {
    while (*input == ' ') {
        ++input;
    }

    if (*input == '(') {
        ++input;

        return read_pair(input, environment);
    } else if (*input == '\'') {
        ++input;

        return read_quotted(input, environment);
    } else {
        return read_symbol(input, environment);
    }
}

#endif
