#ifndef INCLUDE_EVAL_H
#define INCLUDE_EVAL_H

#include "sexpr.h"
#include "env.h"

int special_quote_p(struct sexpr *form, struct env *environment) {
    char *quote_str = get_binding("QUOTE", environment)->symbol;

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(quote_str, form->pair->head->symbol) == 0;
    }

    printf("special_quote_p - undefined form type\n");
    exit(1);
}

int special_list_p(struct sexpr *form, struct env *environment) {
    char *list_str = get_binding("LIST", environment)->symbol;

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(list_str, form->pair->head->symbol) == 0;
    }

    printf("special_list_p - undefined form type\n");
    exit(1);
}

int special_head_p(struct sexpr *form, struct env *environment) {
    char *head_str = get_binding("HEAD", environment)->symbol;

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(head_str, form->pair->head->symbol) == 0;
    }

    printf("special_head_p - undefined form type\n");
    exit(1);
}

int special_tail_p(struct sexpr *form, struct env *environment) {
    char *tail_str = get_binding("TAIL", environment)->symbol;

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(tail_str, form->pair->head->symbol) == 0;
    }

    printf("special_tail_p - undefined form type\n");
    exit(1);
}

int special_eq_p(struct sexpr *form, struct env *environment) {
    char *eq_str = get_binding("EQ", environment)->symbol;

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(eq_str, form->pair->head->symbol) == 0;
    }

    printf("special_eq_p - undefined form type\n");
    exit(1);
}

int special_defvar_p(struct sexpr *form, struct env *environment) {
    char *defvar_str = get_binding("DEFVAR", environment)->symbol;

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(defvar_str, form->pair->head->symbol) == 0;
    }

    printf("special_defvar_p - undefined form type\n");
    exit(1);
}

int self_evaluating_p(struct sexpr *form, struct env *environment) {
    char *nil_str = get_binding("NIL", environment)->symbol;

    if (form->type == SYMBOL) {
        if (strcmp(nil_str, form->symbol) == 0) {
            return 1;
        }
    }

    return 0;
}

struct sexpr *interpret_quote(struct pair *arg, struct env *environment) {
    return arg->head;
}

struct pair *eval_pair(struct pair *p, struct env *environment);

struct sexpr *interpret_list(struct pair *arg, struct env *environment) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_pair(arg, environment);

    return result;
}

struct sexpr *eval_sexpr(struct sexpr *form, struct env *environment);

struct sexpr *interpret_head(struct pair *arg, struct env *environment) {
    return eval_sexpr(arg->head, environment)->pair->head;
}

struct sexpr *interpret_tail(struct pair *arg, struct env *environment) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_sexpr(arg->head, environment)->pair->tail;

    return result;
}

struct sexpr *interpret_eq(struct pair *arg, struct env *environment) {
    arg = eval_pair(arg, environment);

    char *t_str = get_binding("T", environment)->symbol;
    char *nil_str = get_binding("NIL", environment)->symbol;

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = nil_str;

    if (arg->head->type == SYMBOL && arg->tail->head->type == SYMBOL
            && arg->head->symbol == arg->tail->head->symbol) {
        result->symbol = t_str;
    }

    return result;
}

struct sexpr *interpret_defvar(struct pair *arg, struct env *environment) {
    struct binding *b = malloc(sizeof(struct binding));
    b->symbol = arg->head->symbol;
    b->expression = eval_sexpr(arg->tail->head, environment);

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = add_shadowing_binding(b, environment)->symbol;

    return result;
}

struct sexpr *eval_symbol(char *symbol, struct env *environment) {
    return get_binding(symbol, environment)->expression;
}

struct pair *eval_pair(struct pair *p, struct env *environment) {
    p->head = eval_sexpr(p->head, environment);

    if (p->tail != NULL) {
        p->tail = eval_pair(p->tail, environment);
    }

    return p;
}

struct sexpr *eval_sexpr(struct sexpr *form, struct env *environment) {
    if (special_quote_p(form, environment)) {
        return interpret_quote(form->pair->tail, environment);
    } else if (special_list_p(form, environment)) {
        return interpret_list(form->pair->tail, environment);
    } else if (special_head_p(form, environment)) {
        return interpret_head(form->pair->tail, environment);
    } else if (special_tail_p(form, environment)) {
        return interpret_tail(form->pair->tail, environment);
    } else if (special_eq_p(form, environment)) {
        return interpret_eq(form->pair->tail, environment);
    } else if (special_defvar_p(form, environment)) {
        return interpret_defvar(form->pair->tail, environment);
    } else if (self_evaluating_p(form, environment)) {
        return form;
    } else if (form->type == SYMBOL) {
        return eval_symbol(form->symbol, environment);
    }

    printf("eval_sexpr - undefined form\n");
    exit(1);
}

#endif
