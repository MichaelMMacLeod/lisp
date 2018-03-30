#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

#include <stdlib.h>
#include <string.h>
#include "sexpr.h"
#include "env.h"
#include "stream.h"
#include "print.h"

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

struct sexpr *sexpr_reader(char curr, FILE *stream, struct env *e);

char *symbol_reader(char curr, FILE *stream, struct env *e) {
    int length = 2;

    char *symbol = malloc(length * sizeof(char));
    symbol[0] = curr;

    while (1) {
        curr = peek_char(stream);

        if (curr == ' ' || curr == '\n' || curr == '\t' || curr == ')') {
            break;
        }

        ++length;
        symbol = realloc(symbol, length * sizeof(char));
        symbol[length - 2] = curr;

        get_char(stream);
    }

    symbol[length - 1] = '\0';

    upcase(symbol);

    return add_null_binding(symbol, e)->symbol;
}

struct pair *list_reader(char curr, FILE *stream, struct env *e) {
    if (curr == ')') {
        return NULL;
    }

    struct pair *result = malloc(sizeof(struct pair));

    if (peek_char(stream) == ')') {
        result->head = NULL;
    } else {
        result->head = sexpr_reader(get_char(stream), stream, e);
    }

    result->tail = list_reader(get_char(stream), stream, e);

    return result;
}

struct sexpr *quote_reader(char curr, FILE *stream, struct env *e) {
    struct sexpr *quotted_sexpr = sexpr_reader(get_char(stream), stream, e);

    struct pair *nil_tail_pair = malloc(sizeof(struct pair));
    nil_tail_pair->head = quotted_sexpr;
    nil_tail_pair->tail = NULL;

    char *quote = get_binding("QUOTE", e)->symbol;
    struct sexpr *quote_sexpr = malloc(sizeof(struct sexpr));
    quote_sexpr->type = SYMBOL;
    quote_sexpr->symbol = quote;

    struct pair *quote_pair = malloc(sizeof(struct pair));
    quote_pair->head = quote_sexpr;
    quote_pair->tail = nil_tail_pair;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = quote_pair;
    
    return result;
}

struct sexpr *sexpr_reader(char curr, FILE *stream, struct env *e) {
    while (curr == ' ' || curr == '\n' || curr == '\t') {
        curr = get_char(stream);
    }

    struct sexpr *result = malloc(sizeof(struct sexpr));

    if (curr == '(') {
        result->type = PAIR;
        result->pair = list_reader(curr, stream, e);
    } else if (curr == '\'') {
        return quote_reader(curr, stream, e);
    } else {
        result->type = SYMBOL;
        result->symbol = symbol_reader(curr, stream, e);
    }
    
    return result;
}

#endif
