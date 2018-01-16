#ifndef INCLUDE_NODE_UTILS_H
#define INCLudE_NODE_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "node.h"

struct Node* node_create(int type, void* val)
{
    struct Node* node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("node_create: out of memory\n");
        exit(1);
    }

    node->type = type;

    switch (type) {
        case SYMBOL:
            {
                node->symbol = val;
            }

            break;
        case INTEGER:
            {
                node->integer = val;
            }

            break;
        default:
            {
                printf("node_create: reached default branch\n");
                exit(1);
            }
    }

    return node;
}

void node_free(struct Node* node)
{
    switch (node->type) {
        case SYMBOL:
            {
                free(node->symbol);
            }

            break;
        case INTEGER:
            {
                free(node->integer);
            }

            break;
        default:
            {
                printf("node_free: reached default branch\n");
                exit(1);
            }
    }

    free(node);
}

#endif
