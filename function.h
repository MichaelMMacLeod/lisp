#ifndef INCLUDE_FUNCTION_H
#define INCLUDE_FUNCTION_H

#include "sexpr.h"
#include "env.h"
#include "eval.h"

// create_function_env - copy an environment and introduce function arg bindings.
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

// eval_function - evaluate a function.
struct sexpr *eval_function(struct function *f, struct pair *args, struct env *e) {
    struct env *function_env = create_function_env(f->args, args, e);

    return eval_sexpr(f->body, function_env);
}

#endif
