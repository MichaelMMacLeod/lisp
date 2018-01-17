/* node_utils.h
 *
 * Defines several helpful Node-related functions.
 *
 *  includes
 *      <stdlib.h>
 *      <stdio.h>
 *      <string.h>
 *      "node.h"
 *
 *  functions
 *      struct Node* node_create (int type, void* val)
 *      void         node_free   (struct Node* node)
 */

#ifndef INCLUDE_NODE_UTILS_H
#define INCLUDE_NODE_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

/* Allocates a node with a given type and value.
*/
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

/* Deallocates a node.
*/
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

size_t node_tosymbol_mem_size(struct Node* node)
{
    switch (node->type) {
        case SYMBOL:
            {
                return sizeof(char) * (strlen(node->symbol) + 1);
            }

            break;
        case INTEGER:
            {
                int i = *node->integer;
                int nchars = 1;
                
                if (i < 0) {
                    i = abs(i);
                    ++nchars;
                }

                do {
                    ++nchars;
                    i /= 10;
                } while (i > 0);

                return sizeof(char) * nchars;
            }

            break;
        default:
            {
                printf("node_tostring_mem_size: reached default branch\n");
                exit(1);
            }
    }
}

Symbol* node_tosymbol(struct Node* node)
{
    switch (node->type) {
        case SYMBOL:
            {
                size_t size = node_tosymbol_mem_size(node);

                Symbol* s = malloc(size);
                if (s == NULL) {
                    printf("node_tosymbol: out of memory\n");
                    exit(1);
                }

                sprintf(s, "%s", node->symbol);

                return s;
            }

            break;
        case INTEGER:
            {
                size_t size = node_tosymbol_mem_size(node);

                Symbol* s = malloc(size);
                if (s == NULL) {
                    printf("node_tosymbol: out of memory\n");
                    exit(1);
                }

                sprintf(s, "%d", *node->integer);

                return s;
            }

            break;
        default:
            printf("node_tostring: reached default branch\n");
            exit(1);
    }
}

#endif
