#ifndef EVAL_NEW_H
#define EVAL_NEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types/sexpr.h"

struct sexpr *eval_symbol(char *symbol, struct map *m);
struct list *eval_list(struct list *p, struct map *m);
struct sexpr *eval_sexpr(struct sexpr *form, struct map *m);
struct item *add(struct item *i, struct map *m);

#include "../c_macros.h"
#include "../types/stream.h"
#include "../types/string.h"
#include "../functions/quote.h"
#include "../functions/eq.h"
#include "../types/map.h"
#include "../env.h"
#include "../functions/print.h"
#include "../types/list.h"
#include "../types/symbol.h"
#include "../functions/read.h"

MAKE_P(quote, QUOTE);
MAKE_P(list, LIST);
MAKE_P(head, HEAD);
MAKE_P(tail, TAIL);
MAKE_P(eq, EQ);
MAKE_P(defvar, DEFVAR);
MAKE_P(lambda, LAMBDA);
MAKE_P(create_map, CREATE-MAP);
MAKE_P(set, SET);
MAKE_P(get, GET);
MAKE_P(read, READ);
MAKE_P(eval, EVAL);
MAKE_P(loop, LOOP);
MAKE_P(print, PRINT);

// interpret_defvar - bind a symbol to an evaluated expression, add to env
struct sexpr *interpret_defvar(struct list *args, struct map *m) {
    struct item *i = malloc(sizeof(struct map));
    i->key = args->head->symbol;
    i->value = eval_sexpr(args->tail->head, m);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = add(i, m)->key;

    return result;
}

// interpret_lambda - create a lambda expression
struct sexpr *interpret_lambda(struct list *args, struct map *m) {
    struct function *f = malloc(sizeof(struct function));

    if (args->head->list != NULL) {
        f->args = args->head->list;
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

struct sexpr *interpret_read(struct list *args, struct map *package) {
    struct stream *s = malloc(sizeof(struct stream));
    
    if (args == NULL) {
        printf("[%p]> ", package);
        
        s->type = STREAM;
        s->stream = stdin;
    } else {
        s->type = STRING_STREAM;
        s->string_stream = eval_sexpr(args->head, package)->string;
    }

    return sexpr_reader(get_char(s), s, package);
}

struct sexpr *interpret_eval(struct list *args, struct map *m) {
    return eval_sexpr(eval_sexpr(args->head, m), m);
}

struct sexpr *interpret_loop(struct list *args, struct map *m) {
    while (1) {
        eval_sexpr(args->head, m);
    }
}

struct sexpr *interpret_print(struct list *args, struct map *m) {
    struct sexpr *evaluated_arg = eval_sexpr(args->head, m);

    print_sexpr_toplevel(evaluated_arg);

    return evaluated_arg;
}

// create_function_env - copy an environment and introduce function arg bindings
struct map *create_function_environment(
        struct list *lambda_bindings, 
        struct list *args, 
        struct map *m) {
    struct map *f_env = copy(m);

    int n_lambda_bindings = 0;
    struct list *curr_lambda_binding = lambda_bindings;

    while (curr_lambda_binding != NULL
            && curr_lambda_binding->head != NULL) {
        ++n_lambda_bindings;
        curr_lambda_binding = curr_lambda_binding->tail;
    }

    curr_lambda_binding = lambda_bindings;
    struct list *curr_arg = args;

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
struct sexpr *eval_function(struct function *f, struct list *args, struct map *m) {
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

// eval_list - evaluate a list
struct list *eval_list(struct list *p, struct map *m) {
    struct list *result = malloc(sizeof(struct list));
    result->head = eval_sexpr(p->head, m);

    if (p->tail != NULL) {
        result->tail = eval_list(p->tail, m);
    } else {
        result->tail = NULL;
    }

    return result;
}

// eval_sexpr - evaluate a sexpr
struct sexpr *eval_sexpr(struct sexpr *form, struct map *m) {
    if (form->type == SYMBOL) {
        return eval_symbol(form->symbol, m);
    } else if (form->type == LIST) {
        if (quote_p(form->list->head->symbol)) {
            return interpret_quote(form->list->tail, m);
        } else if (list_p(form->list->head->symbol)) {
            return interpret_list(form->list->tail, m);
        } else if (head_p(form->list->head->symbol)) {
            return interpret_head(form->list->tail, m);
        } else if (tail_p(form->list->head->symbol)) {
            return interpret_tail(form->list->tail, m);
        } else if (eq_p(form->list->head->symbol)) {
            return interpret_eq(form->list->tail, m);
        } else if (defvar_p(form->list->head->symbol)) {
            return interpret_defvar(form->list->tail, m);
        } else if (lambda_p(form->list->head->symbol)) {
            return interpret_lambda(form->list->tail, m);
        } else if (create_map_p(form->list->head->symbol)) {
            return interpret_create_map(form->list->tail, m);
        } else if (set_p(form->list->head->symbol)) {
            return interpret_set(form->list->tail, m);
        } else if (get_p(form->list->head->symbol)) {
            return interpret_get(form->list->tail, m);
        } else if (read_p(form->list->head->symbol)) {
            return interpret_read(form->list->tail, m);
        } else if (eval_p(form->list->head->symbol)) {
            return interpret_eval(form->list->tail, m);
        } else if (loop_p(form->list->head->symbol)) {
            return interpret_loop(form->list->tail, m);
        } else if (print_p(form->list->head->symbol)) {
            return interpret_print(form->list->tail, m);
        } else if (form->list->head->type == FUNCTION) {
            return eval_function(form->list->head->function, form->list->tail, m);
        } else {
            struct sexpr *result = malloc(sizeof(struct sexpr));
            result->type = LIST;
            result->list = form->list;

            result->list->head = eval_sexpr(result->list->head, m);

            return eval_sexpr(result, m);
        }
    } else if (form->type == FUNCTION) {
        printf("[eval_sexpr] - unbound symbol\n");
        exit(1);
    } else if (form->type == STRING) {
        return eval_string(form->string);
    } else {
        printf("[eval_sexpr] - undefined sexpr type\n");
        exit(1);
    }
}

#endif
