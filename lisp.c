#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define loop while (1) 
#define MAX_SYMBOL_SIZE 64

/* Can be either a symbol, integer, or boolean value. */
struct Atom {
    enum {SYMBOL, INTEGER, BOOLEAN} type;
    union {
        char* symbol;
        int integer;
        int boolean;
    };
};

/* Returns the result of adding two integer Atoms */
int integer_add(struct Atom* atom1, struct Atom* atom2) {
    if (atom1->type != INTEGER) {
        printf("integer_add: first Atom is not an integer\n");
        exit(1);
    }

    if (atom2->type != INTEGER) {
        printf("integer_add: second Atom is not an integer\n");
        exit(1);
    }

    return atom1->integer + atom2->integer;
}

/* Converts an Atom's value to a char* */
void atom_string(struct Atom* atom, char* str) {
    switch (atom->type) {
        case SYMBOL:
            sprintf(str, "%s", atom->symbol);
            break;
        case INTEGER:
            sprintf(str, "%d", atom->integer);
            break;
        case BOOLEAN:
            if (atom->boolean) {
                sprintf(str, "true");
            } else {
                sprintf(str, "false");
            }
            break;
        default:
            printf("atom_string: default branch reached\n");
            exit(1);
    }
}

void print_atom(struct Atom* atom) {
    char str[MAX_SYMBOL_SIZE];
    atom_string(atom, str);
    printf("%s", str);
}

struct Expr {
    struct Atom* node;
    struct Expr* children;
    int nchildren;
};

/* Prints an Expr like this
 *  (+ (+ 2 3) (+ 4 5))
 * without a newline.
 */
void print_expr(struct Expr* expr) {
    int has_children = expr->nchildren > 0;

    if (has_children) {
        printf("(");
    }

    print_atom(expr->node);

    if (has_children) {
        printf(" ");
    }

    struct Expr* children = expr->children;

    for (int i = 0; i < expr->nchildren; ++i) {
        print_expr(children);

        if (i + 1 != expr->nchildren) {
            printf(" ");
        }

        ++children;
    }

    if (has_children) {
        printf(")");
    }
}

/* Evaluates an expression. The evaluation is done in-place, meaning that
 * the result will be stored in the same memory location that is passed
 * to this function.
 */
void eval_expr(struct Expr* expr) {
    struct Expr* eval_pointer = expr->children;

    for (int i = 0; i < expr->nchildren; ++i) {
        eval_expr(eval_pointer);

        ++eval_pointer;
    }

    eval_pointer = expr;

    switch (eval_pointer->node->type) {
        case SYMBOL:
            if (eval_pointer->node->symbol == "+") {
                int result = integer_add(
                        eval_pointer->children->node,
                        (eval_pointer->children + 1)->node);

                eval_pointer->nchildren = 0;
                eval_pointer->node->type = INTEGER;
                eval_pointer->node->integer = result;
            } else {
                printf("eval_expr: unknown symbol");
                exit(1);
            }
            break;
        case INTEGER:
            break;
        case BOOLEAN:
            break;
        default:
            printf("eval_expr: default branch reached\n");
            exit(1);
    }
}

int atom_type(char* str) {
    if (*str >= '0' && *str <= '9') {
        return INTEGER;
    }

    if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
        return BOOLEAN;
    }

    return SYMBOL;
}

void parse_atom(char* str, struct Atom* result) {
    switch (atom_type(str)) {
        case INTEGER:
            result->type = INTEGER;
            result->integer = strtol(str, NULL, 10);
            break;
        case BOOLEAN:
            result->type = BOOLEAN;
            if (strcmp(str, "true") == 0) {
                result->boolean = 1;
            } else if (strcmp(str, "false") == 0) {
                result->boolean = 0;
            } else {
                printf("parse_atom: str is not actually boolean");
                exit(1);
            }
            break;
        case SYMBOL:
            result->type = SYMBOL;
            result->symbol = str;
            break;
        default:
            printf("parse_atom: default branch reached\n");
            exit(1);
            break;
    }
}

int main() {
    printf("press <enter> to evaluate an expression, <ctrl+c> to exit\n");

    loop {
        printf("lisp> ");

        size_t buffer_size = sizeof(char) * 1024;
        char* buffer = malloc(buffer_size);
        if (buffer = NULL) {
            printf("main: malloc call returned NULL");
            exit(1);
        }
        int chars = getline(&buffer, &buffer_size, stdin);

        buffer[chars - 1] = '\0'; // remove newline from end of buffer

        printf("%d\n", atom_type(buffer));

        free(buffer);
    }

    return 0;
}
/*
   struct Atom a, b, c, d, e, f, g;

   a.type = SYMBOL;
   b.type = SYMBOL;
   c.type = INTEGER;
   d.type = INTEGER;
   e.type = SYMBOL;
   f.type = INTEGER;
   g.type = INTEGER;

   a.symbol = "+";
   b.symbol = "+";
   c.integer = 2;
   d.integer = 3;
   e.symbol = "+";
   f.integer = 4;
   g.integer = 5;

   struct Expr ax, bx, cx, dx, ex, fx, gx;

   ax.node = &a;
   bx.node = &b;
   cx.node = &c;
   dx.node = &d;
   ex.node = &e;
   fx.node = &f;
   gx.node = &g;

   cx.nchildren = 0;
   dx.nchildren = 0;
   fx.nchildren = 0;
   gx.nchildren = 0;

   struct Expr bx_children[] = { cx, dx };
   bx.children = bx_children;
   bx.nchildren = 2;

   struct Expr ex_children[] = { fx, gx };
   ex.children = ex_children;
   ex.nchildren = 2;

   struct Expr ax_children[] = { bx, ex };
   ax.children = ax_children;
   ax.nchildren = 2;

   eval_expr(&ax);
   print_expr(&ax);
   printf("\n");
   */

