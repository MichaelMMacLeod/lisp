#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sexpr.h"
#include "map.h"
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

struct sexpr *sexpr_reader(char curr, struct stream *s, struct map *m);

char *symbol_reader(char curr, struct stream *s, struct map *m) {
    int length = 2;

    char *symbol = malloc(length * sizeof(char));
    symbol[0] = curr;

    while (1) {
        curr = peek_char(s);

        if (curr == ' ' || curr == '\n' || curr == '\t' || curr == ')') {
            break;
        }

        ++length;
        symbol = realloc(symbol, length * sizeof(char));
        symbol[length - 2] = curr;

        get_char(s);
    }

    symbol[length - 1] = '\0';

    upcase(symbol);

    return add_null_bound(symbol, m)->key;
}

struct pair *list_reader(char curr, struct stream *s, struct map *m) {
    if (curr == ')') {
        return NULL;
    }

    struct pair *result = malloc(sizeof(struct pair));

    if (peek_char(s) == ')') {
        result->head = NULL;
    } else {
        result->head = sexpr_reader(get_char(s), s, m);
    }

    result->tail = list_reader(get_char(s), s, m);

    return result;
}

struct sexpr *string_reader(char curr, struct stream *s, struct map *m) {
    char *string = malloc(1 * sizeof(char));
    int length = 1;

    while (1) {
        curr = peek_char(s);

        if (curr == '"') {
            break;
        }

        ++length;
        string = realloc(string, length * sizeof(char));
        string[length - 2] = curr;

        get_char(s);
    }

    get_char(s);

    string[length - 1] = '\0';

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = STRING;
    result->string = string;

    return result;
}

struct sexpr *quote_reader(char curr, struct stream *s, struct map *m) {
    struct sexpr *quotted_sexpr = sexpr_reader(get_char(s), s, m);

    struct pair *nil_tail_pair = malloc(sizeof(struct pair));
    nil_tail_pair->head = quotted_sexpr;
    nil_tail_pair->tail = NULL;

    char *quote = get("QUOTE", m)->key;
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

struct sexpr *sexpr_reader(char curr, struct stream *s, struct map *m) {
    while (curr == ' ' || curr == '\n' || curr == '\t') {
        curr = get_char(s);
    }

    struct sexpr *result = malloc(sizeof(struct sexpr));

    if (curr == '(') {
        result->type = PAIR;
        result->pair = list_reader(curr, s, m);
    } else if (curr == '\'') {
        return quote_reader(curr, s, m);
    } else if (curr == '"') {
        return string_reader(curr, s, m);
    } else {
        result->type = SYMBOL;
        result->symbol = symbol_reader(curr, s, m);
    }
    
    return result;
}

#endif
