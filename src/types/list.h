#ifndef INCLUDE_TYPES_LIST_H
#define INCLUDE_TYPES_LIST_H

struct list {
    struct sexpr *head;
    struct list *tail;
};

#endif
