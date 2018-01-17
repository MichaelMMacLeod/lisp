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

struct Tree* read(char* expr)
{
    struct Tree* tree = NULL;
    char* p = expr;

    if (*p == '(') {
        ++p;

        tree = read_make_leaf(p);

        while (*p != ' ' && *p != ')' && *p != '\0') {
            ++p;
        }

        while (*p == ' ') {
            ++p;
        }

        if (*p == ')') {
            tree->child = NULL;
            return tree;
        }
        
        int nchildren = 0;

        while (*p != '\0') {
            if (nchildren != 0) {
                tree->child = realloc(
                        tree->child,
                        sizeof(struct Tree) * nchildren);

                tree->child[nchildren] = *read(p);
            } else {
                tree->child = read(p);
            }

            ++nchildren;

            //struct Tree* child = tree->child + nchildren;
            //tree->child[nchildren] = *read(p);
            //child = read(p);

            int openparen = 0;

            do {
                if (*p == '(') 
                    ++openparen;
                else if (*p == ')')
                    --openparen;

                ++p;
            } while (openparen != 0);

            while (*p == ' ') {
                ++p;
            }

            break;
        }
    } else if (*p == ')') {
        tree = NULL; // for clarity
    } else {
        tree = read_make_leaf(p);
    }

    return tree;
}

#endif
