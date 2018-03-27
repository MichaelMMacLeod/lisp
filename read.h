#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

#include "sexpr.h"
#include "map.h"
#include "package.h"
#include <string.h>

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

// read_symbol - read a '\0'-delimited string and intern it in a packge.
//
// read_symbol will convert the symbol to full upercase. This helps the
// programmer determine wether text has been passed through the reader or not.
//
// If the symbol is already present in the package, read_symbol will use its
// existing reference. This means that reading the symbol "hello" twice will
// result in one symbol, "HELLO", interned in the package, with each call to
// read_symbol returning a sexpr with a reference to that one symbol.
struct sexpr *read_symbol(char *input, struct map *package) {
    char *symbol = copy_head_str(input);

    struct map_item *item = malloc(sizeof(struct map_item));
    item->name = symbol;
    item->binding = NULL;
    
    item = intern(item, package);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = item->name;

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

struct sexpr *read_sexpr(char *input, struct map *package);

// read_pair - read a linked list from a string until the ending ')'.
//
// The begining '(' should NOT be included when calling read_pair.
struct sexpr *read_pair(char *input, struct map *package) {
    while (*input == ' ') {
        ++input;
    }

    if (*input == ')') {
        return NULL;
    }

    char *head_str = copy_head_str(input);
    struct sexpr *head = read_sexpr(head_str, package);

    char *tail_str_pos = tail_str(input);
    struct sexpr *tail = read_pair(tail_str_pos, package);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;

    if (tail == NULL) {
        result->pair = cons(head, NULL);
    } else {
        result->pair = cons(head, tail->pair);
    }

    return result;
}

struct sexpr *read_quotted(char *input, struct map *package) {
    char *quote_str = malloc(7 * sizeof(char));
    strcpy(quote_str, "QUOTE");

    struct sexpr *quotted_sexpr = malloc(sizeof(struct sexpr));
    quotted_sexpr->type = SYMBOL;
    quotted_sexpr->symbol = quote_str;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;

    result->pair = malloc(sizeof(struct pair));

    struct pair *quotted_pair = malloc(sizeof(struct pair));
    quotted_pair->head = read_sexpr(input, package);
    quotted_pair->tail = NULL;

    result->pair->head = quotted_sexpr;
    result->pair->tail = quotted_pair;

    return result;
}

// read_sexpr - read an s-expression.
struct sexpr *read_sexpr(char *input, struct map *package) {
    while (*input == ' ') {
        ++input;
    }

    if (*input == '(') {
        ++input;

        return read_pair(input, package);
    } else if (*input == '\'') {
        ++input;

        return read_quotted(input, package);
    } else {
        return read_symbol(input, package);
    }
}

#endif
