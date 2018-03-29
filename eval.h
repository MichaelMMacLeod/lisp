#ifndef EVAL_NEW_H
#define EVAL_NEW_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sexpr.h"
#include "env.h"

struct sexpr *eval_symbol(char *symbol, struct env *e);
struct pair *eval_pair(struct pair *p, struct env *e);
struct sexpr *eval_sexpr(struct sexpr *form, struct env *e);

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
struct sexpr *interpret_quote(struct pair *args, struct env *e) {
    return args->head;
}

// interpret_list - evaluate each argument and place them in a list
struct sexpr *interpret_list(struct pair *args, struct env *e) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_pair(args, e);

    return result;
}

// interpret_head - evaluate the list, then return its head
struct sexpr *interpret_head(struct pair *args, struct env *e) {
    return eval_sexpr(args->head, e)->pair->head;
}

// interpret_tail - evaluate the list, then return its tail
struct sexpr *interpret_tail(struct pair *args, struct env *e) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_sexpr(args->head, e)->pair->tail;

    return result;
}

// interpret_eq - evaluate the arguments. T if they are equal, NIL otherwise
struct sexpr *interpret_eq(struct pair *args, struct env *e) {
    args = eval_pair(args, e);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;

    if (args->head->type == SYMBOL && args->tail->head->type == SYMBOL
            && args->head->symbol == args->tail->head->symbol) {
        result->symbol = get_binding("T", e)->symbol;
    } else {
        result->symbol = get_binding("NIL", e)->symbol;
    }

    return result;
}

// interpret_defvar - bind a symbol to an evaluated expression, add to env
struct sexpr *interpret_defvar(struct pair *args, struct env *e) {
    struct binding *b = malloc(sizeof(struct binding));
    b->symbol = args->head->symbol;
    b->expression = eval_sexpr(args->tail->head, e);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = add_shadowing_binding(b, e)->symbol;

    return result;
}

// interpret_lambda - create a lambda expression
struct sexpr *interpret_lambda(struct pair *args, struct env *e) {
    struct function *f = malloc(sizeof(struct function));

    if (args->head != NULL) {
        f->args = args->head->pair;
    } else {
        f->args = NULL;
    }

    f->body = args->tail->head;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = FUNCTION;
    result->function = f;

    return result;
}

// create_function_env - copy an environment and introduce function arg bindings
struct env *create_function_env(struct pair *lambda_bindings, 
                                struct pair *args, 
                                struct env *e) {
    struct env *function_env = copy_env(e);

    int n_lambda_bindings = 0;
    struct pair *curr_lambda_binding = lambda_bindings;

    while (curr_lambda_binding != NULL) {
        ++n_lambda_bindings;
        curr_lambda_binding = curr_lambda_binding->tail;
    }

    curr_lambda_binding = lambda_bindings;
    struct pair *curr_arg = args;

    for (int i = 0; i < n_lambda_bindings; ++i) {
        struct binding *b = malloc(sizeof(struct binding));
        b->symbol = curr_lambda_binding->head->symbol;
        b->expression = eval_sexpr(curr_arg->head, e);

        add_shadowing_binding(b, function_env);

        curr_lambda_binding = curr_lambda_binding->tail;
        curr_arg = curr_arg->tail;
    }

    return function_env;
}

// eval_function - evaluate a function
struct sexpr *eval_function(struct function *f, struct pair *args, struct env *e) {
    struct env *function_env = create_function_env(f->args, args, e);

    return eval_sexpr(f->body, function_env);
}

// eval_symbol - evaluate a symbol
struct sexpr *eval_symbol(char *symbol, struct env *e) {
    if (symbol_string_eq("NIL", symbol)) {
        struct sexpr *result = malloc(sizeof(struct sexpr));
        result->type = SYMBOL;
        result->symbol = symbol;

        return result;
    } else {
        struct binding *b = get_binding(symbol, e);

        if (b != NULL) {
            return b->expression;
        } else {
            printf("[eval_symbol] - unbound symbol\n");
            exit(1);
        }
    }
}

// eval_pair - evaluate a pair
struct pair *eval_pair(struct pair *p, struct env *e) {
    struct pair *result = malloc(sizeof(struct pair));
    result->head = eval_sexpr(p->head, e);

    if (p->tail != NULL) {
        result->tail = eval_pair(p->tail, e);
    }

    return result;
}

// eval_sexpr - evaluate a sexpr
struct sexpr *eval_sexpr(struct sexpr *form, struct env *e) {
    if (form->type == SYMBOL) {
        return eval_symbol(form->symbol, e);
    } else if (form->type == PAIR) {
        if (quote_p(form->pair->head->symbol)) {
            return interpret_quote(form->pair->tail, e);
        } else if (list_p(form->pair->head->symbol)) {
            return interpret_list(form->pair->tail, e);
        } else if (head_p(form->pair->head->symbol)) {
            return interpret_head(form->pair->tail, e);
        } else if (tail_p(form->pair->head->symbol)) {
            return interpret_tail(form->pair->tail, e);
        } else if (eq_p(form->pair->head->symbol)) {
            return interpret_eq(form->pair->tail, e);
        } else if (defvar_p(form->pair->head->symbol)) {
            return interpret_defvar(form->pair->tail, e);
        } else if (lambda_p(form->pair->head->symbol)) {
            return interpret_lambda(form->pair->tail, e);
        } else if (form->pair->head->type == FUNCTION) {
            return eval_function(form->pair->head->function, form->pair->tail, e);
        } else {
            struct sexpr *result = malloc(sizeof(struct sexpr));
            result->type = PAIR;
            result->pair = form->pair;

            result->pair->head = eval_sexpr(result->pair->head, e);

            return eval_sexpr(result, e);
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
