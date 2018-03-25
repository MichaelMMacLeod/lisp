#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../read.h"

int read_symbol_is_correct_symbol() {
    struct map *package = malloc(sizeof(struct map));
    package->size = 0;
    package->items = malloc(0);

    char *str = malloc(6 * sizeof(char));
    strcpy(str, "hello");

    char *intended_result = malloc(6 * sizeof(char));
    strcpy(intended_result, "HELLO");

    struct sexpr *result = read_symbol(str, package);

    int is_correct_symbol = strcmp(result->symbol, intended_result) == 0;

    return is_correct_symbol;
}

int read_symbol_has_correct_type() {
    struct map *package = malloc(sizeof(struct map));
    package->size = 0;
    package->items = malloc(0);

    char *str = malloc(6 * sizeof(char));
    strcpy(str, "hello");

    char *intended_result = malloc(6 * sizeof(char));
    strcpy(intended_result, "HELLO");

    struct sexpr *result = read_symbol(str, package);

    int has_correct_type = result->type == SYMBOL;

    return has_correct_type;
}

int read_symbol_interns_uninterned_symbol() {
    struct map *package = malloc(sizeof(struct map));
    package->size = 0;
    package->items = malloc(0);

    char *str = malloc(6 * sizeof(char));
    strcpy(str, "hello");

    struct sexpr *result = read_symbol(str, package);

    int interns_uninterned_symbol = package->items[0].name == result->symbol;
    
    return interns_uninterned_symbol;
}

int read_symbol_returns_interned_symbol() {
    struct map *package = malloc(sizeof(struct map));
    package->size = 0;
    package->items = malloc(0);

    char *str = malloc(6 * sizeof(char));
    strcpy(str, "HELLO");

    struct map_item *item = malloc(sizeof(struct map_item));
    item->name = str;

    add(package, item);

    char *str_to_read = malloc(6 * sizeof(char));
    strcpy(str_to_read, "hello");

    struct sexpr *result = read_symbol(str_to_read, package);

    int returns_interned_symbol = package->items[0].name == result->symbol;
    
    return returns_interned_symbol;
}

int main() {
    if (read_symbol_has_correct_type()) {
        printf("read_symbol_has_correct_type - pass\n");
    } else {
        printf("read_symbol_has_correct_type - fail\n");
    }

    if (read_symbol_is_correct_symbol()) {
        printf("read_symbol_is_correct_symbol - pass\n");
    } else {
        printf("read_symbol_is_correct_symbol - fail\n");
    }

    if (read_symbol_interns_uninterned_symbol()) {
        printf("read_symbol_interns_uninterned_symbol - pass\n");
    } else {
        printf("read_symbol_interns_uninterned_symbol - fail\n");
    }

    if (read_symbol_returns_interned_symbol()) {
        printf("read_symbol_returns_interned_symbol - pass\n");
    } else {
        printf("read_symbol_returns_interned_symbol - fail\n");
    }
}
