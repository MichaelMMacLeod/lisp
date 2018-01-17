#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include <stdlib.h>
#include <stdio.h>

struct Rc {
    void* ref;
    int* count;
};

struct Rc* rc_create(size_t size)
{
    struct Rc* rc = malloc(sizeof(struct Rc));
    if (rc == NULL) {
        printf("rc_malloc: out of memory.\n");
        exit(1);
    }

    void* data = malloc(size);
    if (data == NULL) {
        printf("rc_malloc: out of memory.\n");
        exit(1);
    }

    int* count = malloc(sizeof(int));
    if (count == NULL) {
        printf("rc_malloc: out of memory.\n");
        exit(1);
    }

    *count = 0;

    rc->ref = data;
    rc->count = count;

    return rc;
}

void* rc_deref(struct Rc* rc)
{
    ++*rc->count;

    return rc->ref;
}

void rc_free(struct Rc* rc)
{
    --*rc->count;

    if (*rc->count == 0) {
        free(rc->ref);
        free(rc->count);
    }
    
    free(rc);
}

#endif
