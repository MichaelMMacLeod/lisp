#ifndef INCLUDE_FUNCTIONS_PRINT_H
#define INCLUDE_FUNCTIONS_PRINT_H

void print_symbol(char *symbol) {
    printf("%s", symbol);
}

void print_sexpr(struct sexpr *s);

void print_list_helper(struct list *p) {
    print_sexpr(p->head);

    if (p->tail != NULL) {
        printf(" ");

        print_list_helper(p->tail);
    }
}

void print_list(struct list *p) {
    printf("(");
    print_list_helper(p);
    printf(")");
}

void print_function(struct function *f) {
    if (f->type == PRIMITIVE) {
        printf(f->primitive);
        return;
    }

    printf("#<FUNCTION (LAMBDA ");

    print_list(f->lambda->args);

    if (f->lambda->body != NULL) {
        printf(" ");
    }

    print_sexpr(f->lambda->body);

    printf(") ");

    printf("[%p]>", f->lambda);
}

void print_map(struct map *m) {
    printf("#<MAP SIZE=%d [%p]>", m->size, m);
}

void print_item(struct item *i) {
    printf("#<ITEM KEY=");
    print_symbol(i->key);

    printf(" VALUE=");

    print_sexpr(i->value);

    printf(">");
}

void print_string(char *string) {
    printf("\"%s\"", string);
}

void print_sexpr(struct sexpr *s) {
    if (s == NULL) {
        return;
    }

    if (s->type == SYMBOL) {
        print_symbol(s->symbol);
    } else if (s->type == LIST) {
        print_list(s->list);
    } else if (s->type == FUNCTION) {
        print_function(s->function);
    } else if (s->type == MAP) {
        print_map(s->map);
    } else if (s->type == ITEM) {
        print_item(s->item);
    } else if (s->type == STRING) {
        print_string(s->string);
    }
}

void print_sexpr_toplevel(struct sexpr *s) {
    printf("\n");
    print_sexpr(s);
    printf("\n");
}

#endif
