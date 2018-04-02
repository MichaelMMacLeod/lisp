#ifndef INCLUDE_EVAL_LIST_H
#define INCLUDE_EVAL_LIST_H

struct sexpr *eval_list(struct sexpr *s, struct map *package) {
    struct sexpr *head = s->list->head;
    struct sexpr *evaled = eval_sexpr(head, package);
    struct function *fn = evaled->function;
    struct list *args = s->list->tail;

    return apply_function(fn, args, package);
}

#endif
