#ifndef INCLUDE_ENV_H
#define INCLUDE_ENV_H

#include "sexpr.h"
#include "map.h"

struct item *add_null_bound(char *key, struct map *m) {
    struct item *i = malloc(sizeof(struct item));
    i->key = key;
    i->value = NULL;

    return add_without_shadowing(i, m);
}

struct map *create_default_environment() {
    size_t cs = sizeof(char);

    char *nil_str = malloc(4 * cs); 
    char *t_str = malloc(2 * cs); 
    char *quote_str = malloc(6 * cs);
    char *list_str = malloc(5 * cs); 
    char *head_str = malloc(5 * cs); 
    char *tail_str = malloc(5 * cs); 
    char *eq_str = malloc(3 * cs); 
    char *defvar_str = malloc(7 * cs); 
    char *lambda_str = malloc(7 * cs); 
    char *create_map_str = malloc(11 * cs);
    char *get_str = malloc(4 * cs);
    char *set_str = malloc(4 * cs);
    char *read_str = malloc(5 * cs);

    strcpy(nil_str, "NIL");
    strcpy(t_str, "T");
    strcpy(quote_str, "QUOTE");
    strcpy(list_str, "LIST");
    strcpy(head_str, "HEAD");
    strcpy(tail_str, "TAIL");
    strcpy(eq_str, "EQ");
    strcpy(defvar_str, "DEFVAR");
    strcpy(lambda_str, "LAMBDA");
    strcpy(create_map_str, "CREATE-MAP");
    strcpy(get_str, "GET");
    strcpy(set_str, "SET");
    strcpy(read_str, "READ");

    struct map *m = create_empty_map();

    add_null_bound(nil_str, m);
    add_null_bound(t_str, m);
    add_null_bound(quote_str, m);
    add_null_bound(list_str, m);
    add_null_bound(head_str, m);
    add_null_bound(tail_str, m);
    add_null_bound(eq_str, m);
    add_null_bound(defvar_str, m);
    add_null_bound(lambda_str, m);
    add_null_bound(create_map_str, m);
    add_null_bound(get_str, m);
    add_null_bound(set_str, m);
    add_null_bound(read_str, m);

    return m;
}

#endif
