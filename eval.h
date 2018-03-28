#ifndef INCLUDE_EVAL_H
#define INCLUDE_EVAL_H

#include "sexpr.h"

int special_quote_p(struct sexpr *form) {
    char *nil_str = "QUOTE";

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(nil_str, form->pair->head->symbol) == 0;
    }

    printf("special_quote_p - undefined form type\n");
    exit(1);
}

int special_list_p(struct sexpr *form) {
    char *list_str = "LIST";

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(list_str, form->pair->head->symbol) == 0;
    }

    printf("special_list_p - undefined form type\n");
    exit(1);
}

int special_head_p(struct sexpr *form) {
    char *head_str = "HEAD";

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(head_str, form->pair->head->symbol) == 0;
    }

    printf("special_head_p - undefined form type\n");
    exit(1);
}

int special_tail_p(struct sexpr *form) {
    char *tail_str = "TAIL";

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(tail_str, form->pair->head->symbol) == 0;
    }

    printf("special_tail_p - undefined form type\n");
    exit(1);
}

int special_eq_p(struct sexpr *form) {
    char *eq_str = "EQ";

    if (form->type == SYMBOL) {
        return 0;
    } else if (form->type == PAIR) {
        return strcmp(eq_str, form->pair->head->symbol) == 0;
    }

    printf("special_eq_p - undefined form type\n");
    exit(1);
}

int self_evaluating_p(struct sexpr *form) {
    char *nil_str = "NIL";

    if (form->type == SYMBOL) {
        if (strcmp(nil_str, form->symbol) == 0) {
            return 1;
        }
    }

    return 0;
}

struct sexpr *interpret_quote(struct pair *arg) {
    return arg->head;
}

struct pair *eval_pair(struct pair *p);

struct sexpr *interpret_list(struct pair *arg) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_pair(arg);

    return result;
}

struct sexpr *eval_sexpr(struct sexpr *form);

struct sexpr *interpret_head(struct pair *arg) {
    return eval_sexpr(arg->head)->pair->head;
}

struct sexpr *interpret_tail(struct pair *arg) {
    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = PAIR;
    result->pair = eval_sexpr(arg->head)->pair->tail;

    return result;
}

struct sexpr *interpret_eq(struct pair *arg) {
    arg = eval_pair(arg);

    char *t_str = malloc(2 * sizeof(char));
    strcpy(t_str, "T");

    char *nil_str = malloc(4 * sizeof(char));
    strcpy(nil_str, "NIL");

    struct sexpr *result = malloc(sizeof(struct sexpr));
    result->type = SYMBOL;
    result->symbol = nil_str;

    if (arg->head->type == SYMBOL && arg->tail->head->type == SYMBOL
            && arg->head->symbol == arg->tail->head->symbol) {
        result->symbol = t_str;
    }

    return result;
}

struct pair *eval_pair(struct pair *p) {
    p->head = eval_sexpr(p->head);

    if (p->tail != NULL) {
        p->tail = eval_pair(p->tail);
    }

    return p;
}

struct sexpr *eval_sexpr(struct sexpr *form) {
    if (special_quote_p(form)) {
        return interpret_quote(form->pair->tail);
    } else if (special_list_p(form)) {
        return interpret_list(form->pair->tail);
    } else if (special_head_p(form)) {
        return interpret_head(form->pair->tail);
    } else if (special_tail_p(form)) {
        return interpret_tail(form->pair->tail);
    } else if (special_eq_p(form)) {
        return interpret_eq(form->pair->tail);
    } else if (self_evaluating_p(form)) {
        return form;
    }

    printf("eval_sexpr - undefined form\n");
    exit(1);
}

#endif
