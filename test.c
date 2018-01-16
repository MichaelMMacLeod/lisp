#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    enum { SYMBOL, INTEGER } type;
    union {
        char** symbol;
        int* integer;
    };
};

struct Node* SYMBOL_create(char** symbol)
{
    struct Node* node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("SYMBOL_create: out of memory\n");
        exit(1);
    }

    node->type = SYMBOL;

    size_t size = sizeof(char) * (strlen(*symbol) + 1);

    node->symbol = malloc(size);
    if (node->symbol == NULL) {
        printf("SYMBOL_create: out of memory\n");
        exit(1);
    }

    memcpy(node->symbol, symbol, size);

    return node;
}

struct Node* INTEGER_create(int* integer)
{
    struct Node* node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("INTEGER_create: out of memory\n");
        exit(1);
    }

    node->type = INTEGER;

    size_t size = sizeof(int);

    node->integer = malloc(size);
    if (node->integer == NULL) {
        printf("INTEGER_create: out of memory\n");
        exit(1);
    }

    memcpy(node->integer, integer, size);

    return node;
}

void node_print(struct Node* node)
{
    switch (node->type) {
        case SYMBOL:
            {
                printf("%s", *node->symbol);
            }

            break;
        case INTEGER:
            {
                printf("%d", *node->integer);
            }

            break;
        default:
            {
                printf("node_print: reached default branch\n");
                exit(1);
            }
    }
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

int main() 
{
    int* i = malloc(sizeof(int));
    *i = 42;

    struct Node* node2 = INTEGER_create(i);
    node_print(node2);

    node_free(node2);
    free(i);

    char* str = malloc(sizeof(char) * 100);
    strcpy(str, "hola?");

    struct Node* node3 = SYMBOL_create(&str);
    node_print(node3);

    node_free(node3);
    free(str);

    return 0;
}
