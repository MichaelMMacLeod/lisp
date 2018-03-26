#ifndef INCLUDE_READ_H
#define INCLUDE_READ_H

#include "sexpr.h"
#include "map.h"
#include <string.h>

char upper_case(char c) {
    if (c >= 97 && c <= 122) {
        return c - 32;
    } else {
        return c;
    }
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
    struct sexpr *result = malloc(sizeof(struct sexpr));

    int size = 1;
    char *p = input;

    while (*p != '\0') {
        ++size;
        ++p;
    }

    char *symbol = malloc(size * sizeof(char));
    char *symbol_start = symbol;

    char c = *input;
    ++input;

    while (c != '\0') {
        *symbol = upper_case(c);

        ++symbol;

        c = *input;
        ++input;
    }

    *symbol = '\0';

    struct map_item *interned_item = get_by_name(package, symbol_start);
    
    if (interned_item == NULL) {
        interned_item = malloc(sizeof(struct map_item));
        interned_item->name = symbol_start;

        add(package, interned_item);

        result->type = SYMBOL;
        result->symbol = symbol_start;
    } else {
        result->type = SYMBOL;
        result->symbol = interned_item->name;
    }

    return result;
}

// cons - construct a linked list.
struct pair *cons(struct sexpr *head, struct pair *tail) {
    struct pair *result = malloc(sizeof(struct pair));

    result->head = head;
    result->tail = tail;

    return result;
}

// copy_head_str - create a '\0' delimited string out of the next valid
// sexpr.
//
// The result points to a copy of a portion of the input.
char *copy_head_str(char *input) {
    char *p = input;

    int size = 0;

    int n_open = 0;

    while (1) {
        if ((*p == ' ' || *p == ')') && n_open == 0) {
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

struct sexpr *read_sexpr(char *input, struct map *package) {
    while (*input == ' ') {
        ++input;
    }

    if (*input == '(') {
        ++input;

        return read_pair(input, package);
    } else {
        return read_symbol(input, package);
    }
}

#endif
