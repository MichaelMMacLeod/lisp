#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef char* Symbol;
typedef int Integer;

typedef struct {
    enum {
        SYMBOL,
        INTEGER
    } type;

    union {
        Symbol* symbol;
        Integer* integer;
    };
} Node;

/* Initializes a Node with a type and data.
 *
 * ex:
 *      node_init(&n, INTEGER, &i) => Node { type = INTEGER, integer = &i }
 *      node_init(&n, SYMBOL, &s)  => Node { type = SYMBOL, symbol = &s }
 */
void node_init(Node* dest, int type, void* data) {
    dest->type = type;

    switch (type) {
        case SYMBOL:
            {
                dest->symbol = data;
            }

            break;
        case INTEGER:
            {
                dest->integer = data;
            }

            break;
        default:
            {
                printf("node_init: Unknown node type `%d`\n", dest->type);
                exit(1);
            }
    }
}

/* Calculates the number of characters required to store the value inside a Node
 * including the '\0' character.
 *
 * ex:
 *      Node { symbol = "12345" } => 6
 *      Node { symbol = "" }      => 1
 *      Node { integer = 10 }     => 3
 *      Node { integer = -1 }     => 3
 *      Node { integer = 0 }      => 2
 *      Node { integer = -0 }     => 2
 */
int node_str_nchars(Node* n) {
    int nchars = 0;

    switch (n->type) {
        case SYMBOL: 
            {
                char* c = *n->symbol;

                while (*c != '\0') {
                    ++nchars;
                    ++c;
                }
            } 
            break;
        case INTEGER: 
            {
                int i = *n->integer;

                if (i < 0) {
                    i = abs(i);
                    ++nchars; // add one for '-'
                }

                do {
                    ++nchars;
                    i /= 10;
                } while (i > 0);
            }
            break;
        default:
            {
                printf("node_str_nchar: Unknown node type `%d`\n", n->type);
                exit(1);
            }
    }

    ++nchars; // add one for '\0'

    return nchars;
}

/* Allocates the proper ammount of memory for storing the data inside a Node in a 
 * string.
 */
char* node_malloc_str(Node* n) {
    return malloc(sizeof(char) * node_str_nchars(n));
}

/* Deposits the data from a Node into a destination string. `dest` should point to
 * the beginning of a space of memory allocated as so:
 *      char* dest = node_malloc_str(&node);
 *
 * ex:
 *      node_str(dest, Node { symbol = "hi" })  => dest = "hi"
 *      node_str(dest, Node { integer = -123 }) => dest = "-123"
 */
void node_str(char* dest, Node* src) {
    char* d = dest;

    switch (src->type) {
        case SYMBOL:
            {
                char* s = *src->symbol;

                while (*s != '\0') {
                    *d = *s;
                    ++d;
                    ++s;
                }
            }

            break;
        case INTEGER:
            {
                int i = *src->integer;

                if (i < 0) {
                    i = abs(i);
                    
                    *d = '-';
                    ++d;
                }

                // point d to where the '\0' should go
                if (i != 0) {
                    d += (int) log10(i) + 1;
                } else {
                    ++d;
                }

                *d = '\0';

                // walk backwards through the number
                do {
                    --d;
                    
                    *d = i % 10 + '0';

                    i /= 10;
                } while (i > 0);
            }

            break;
        default:
            {
                printf("node_str: Unknown Node type `%d`", src->type);
                exit(1);
            }
    }
}

/* Prints a node without a newline. 
 *
 * ex:
 *      Node { symbol = "Hello world!" } => Hello world!
 *      Node { integer = -123 }          => -123
 */
void node_print(Node* n) {
    char* dest = node_malloc_str(n);
    node_str(dest, n);

    printf("%s", dest);

    free(dest);
}

#endif
