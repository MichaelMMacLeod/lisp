#ifndef INCLUDE_REPL_H
#define INCLUDE_REPL_H

#include <stdio.h>
#include <string.h>
#include "../types/tree/tree.h"
#include "../types/tree/tree_utils.h"
#include "../types/node/node.h"
#include "../types/node/node_utils.h"

int determine_node_type(char* str)
{
    char* p = str;

    int p_integer = 1;
    int p_symbol = 1;

    // is str an integer?
    while (*p != '\0') {
        if (!(*p >= '0' && *p <= '9')) {
            p_integer = 0;
            break;
        }

        ++p;
    }

    if (p_integer)
        return INTEGER;

    if (p_symbol)
        return SYMBOL;

    printf("determine_node_type: can't determine node type\n");
    exit(1);
}

struct Tree* read_make_leaf(char* expr)
{
    char* p = expr;

    char* start = expr;
    char* end = NULL;

    while (*p != ' ' && *p != ')' && *p != '\0') {
        ++p;
    }

    end = p;

    int nchars = end - start;

    char* strc = malloc(sizeof(char) * nchars);
    if (strc == NULL) {
        printf("read_make_leaf: out of memory\n");
        exit(1);
    }

    strncpy(strc, expr, nchars);
    strc[nchars] = '\0';

    struct Node* node = NULL;

    switch (determine_node_type(strc)) {
        case SYMBOL:
            {
                node = node_create(SYMBOL, strc);
            }

            break;
        case INTEGER:
            {
                int i = strtol(strc, NULL, 10);
                node = node_create(INTEGER, &i);
            }

            break;
        default:
            printf("read_make_leaf: don't recognise node type\n");
            exit(1);
    }
    
    struct Tree* leaf = tree_create_leaf(node);

    return leaf;
}

#endif
