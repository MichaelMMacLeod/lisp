#ifndef EVAL_NEW_H
#define EVAL_NEW_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sexpr.h"
#include "map.h"
#include "env.h"

struct sexpr *eval_symbol(char *symbol, struct map *m);
struct pair *eval_pair(struct pair *p, struct map *m);
struct sexpr *eval_sexpr(struct sexpr *form, struct map *m);

// quote_p - true if the symbol is QUOTE
int quote_p(char *symbol) {
    return strcmp("QUOTE", symbol) == 0;
}

// list_p - true if the symbol is LIST
int list_p(char *symbol) {
    return strcmp("LIST", symbol) == 0;
}

// head_p - true if the symbol is HEAD
int head_p(char *symbol) {
    return strcmp("HEAD", symbol) == 0;
}

// tail_p - true if the symbol is TAIL
int tail_p(char *symbol) {
    return strcmp("TAIL", symbol) == 0;
}

// eq_p - true if the symbol is EQ
int eq_p(char *symbol) {
    return strcmp("EQ", symbol) == 0;
}

// defvar_p - true if the symbol is DEFVAR
int defvar_p(char *symbol) {
    return strcmp("DEFVAR", symbol) == 0;
}

// lambda_p - true if the symbol is LAMBDA
int lambda_p(char *symbol) {
    return strcmp("LAMBDA", symbol) == 0;
}

// interpret_quote - return the argument unevaluated
struct sexpr *interpret_quote(struct pair *args, struct map *m) {
    return args->head;
}

// interpret_list - evaluate each argument and place them in a list
struct sexpr *interpret_list(struct pair *args, struct map *m) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_pair(args, m);

    return result;
}

// interpret_head - evaluate the list, then return its head
struct sexpr *interpret_head(struct pair *args, struct map *m) {
    return eval_sexpr(args->head, m)->pair->head;
}

// interpret_tail - evaluate the list, then return its tail
struct sexpr *interpret_tail(struct pair *args, struct map *m) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_sexpr(args->head, m)->pair->tail;

    return result;
}

// interpret_eq - evaluate the arguments. T if they are equal, NIL otherwise
struct sexpr *interpret_eq(struct pair *args, struct map *m) {
    args = eval_pair(args, m);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;

    if (args->head->type == SYMBOL && args->tail->head->type == SYMBOL
            && args->head->symbol == args->tail->head->symbol) {
        result->symbol = get("T", m)->key;
    } else {
        result->symbol = get("NIL", m)->key;
    }

    return result;
}

// interpret_defvar - bind a symbol to an evaluated expression, add to env
struct sexpr *interpret_defvar(struct pair *args, struct map *m) {
    struct item *i = malloc(sizeof(struct map));
    i->key = args->head->symbol;
    i->value = eval_sexpr(args->tail->head, m);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = add(i, m)->key;

    return result;
}

// interpret_lambda - create a lambda expression
struct sexpr *interpret_lambda(struct pair *args, struct map *m) {
    struct function *f = malloc(sizeof(struct function));

    if (args->head->pair != NULL) {
        f->args = args->head->pair;
    } else {
        f->args = NULL;
    }

    if (args->tail != NULL) {
        f->body = args->tail->head;
    } else {
        f->body = NULL;
    }

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = FUNCTION;
    result->function = f;

    return result;
}

// create_function_env - copy an environment and introduce function arg bindings
struct map *create_function_environment(
        struct pair *lambda_bindings, 
        struct pair *args, 
        struct map *m) {
    struct map *f_env = copy(m);

    int n_lambda_bindings = 0;
    struct pair *curr_lambda_binding = lambda_bindings;

    while (curr_lambda_binding != NULL
            && curr_lambda_binding->head != NULL) {
        ++n_lambda_bindings;
        curr_lambda_binding = curr_lambda_binding->tail;
    }

    curr_lambda_binding = lambda_bindings;
    struct pair *curr_arg = args;

    for (int j = 0; j < n_lambda_bindings; ++j) {
        struct item *i = malloc(sizeof(struct item));
        i->key = curr_lambda_binding->head->symbol;
        i->value = eval_sexpr(curr_arg->head, m);

        add(i, f_env);

        curr_lambda_binding = curr_lambda_binding->tail;
        curr_arg = curr_arg->tail;
    }

    return f_env;
}

// eval_function - evaluate a function
struct sexpr *eval_function(struct function *f, struct pair *args, struct map *m) {
    struct map *f_env = create_function_environment(f->args, args, m);

    return eval_sexpr(f->body, f_env);
}

// eval_symbol - evaluate a symbol
struct sexpr *eval_symbol(char *symbol, struct map *m) {
    if (strcmp("NIL", symbol) == 0) {
        struct sexpr *result = malloc(sizeof(struct sexpr));
        result->type = SYMBOL;
        result->symbol = symbol;

        return result;
    } else {
        struct item *i = get(symbol, m);

        if (i != NULL) {
            return i->value;
        } else {
            printf("[eval_symbol] - unbound symbol\n");
            exit(1);
        }
    }
}

// eval_pair - evaluate a pair
struct pair *eval_pair(struct pair *p, struct map *m) {
    struct pair *result = malloc(sizeof(struct pair));
    result->head = eval_sexpr(p->head, m);

    if (p->tail != NULL) {
        result->tail = eval_pair(p->tail, m);
    } else {
        result->tail = NULL;
    }

    return result;
}

// eval_sexpr - evaluate a sexpr
struct sexpr *eval_sexpr(struct sexpr *form, struct map *m) {
    if (form->type == SYMBOL) {
        return eval_symbol(form->symbol, m);
    } else if (form->type == PAIR) {
        if (quote_p(form->pair->head->symbol)) {
            return interpret_quote(form->pair->tail, m);
        } else if (list_p(form->pair->head->symbol)) {
            return interpret_list(form->pair->tail, m);
        } else if (head_p(form->pair->head->symbol)) {
            return interpret_head(form->pair->tail, m);
        } else if (tail_p(form->pair->head->symbol)) {
            return interpret_tail(form->pair->tail, m);
        } else if (eq_p(form->pair->head->symbol)) {
            return interpret_eq(form->pair->tail, m);
        } else if (defvar_p(form->pair->head->symbol)) {
            return interpret_defvar(form->pair->tail, m);
        } else if (lambda_p(form->pair->head->symbol)) {
            return interpret_lambda(form->pair->tail, m);
        } else if (form->pair->head->type == FUNCTION) {
            return eval_function(form->pair->head->function, form->pair->tail, m);
        } else {
            struct sexpr *result = malloc(sizeof(struct sexpr));
            result->type = PAIR;
            result->pair = form->pair;

            result->pair->head = eval_sexpr(result->pair->head, m);

            return eval_sexpr(result, m);
        }
    } else if (form->type == FUNCTION) {
        printf("[eval_sexpr] - unbound symbol\n");
        exit(1);
    } else {
        printf("[eval_sexpr] - undefined sexpr type\n");
        exit(1);
    }
}

#endif
