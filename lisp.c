#include <stdio.h>
#include <stdlib.h>

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

void print_expr(struct Expr* expr) {
    int has_children = expr->nchildren > 0;

    if (has_children) {
        printf("(");
    }

    print_atom(expr->node);

    if (has_children) {
        printf(" ");
    }

    for (int i = 0; i < expr->nchildren; ++i) {
        print_expr(expr->children);

        if (i + 1 != expr->nchildren) {
            printf(" ");
        }

        ++expr->children;
    }

    if (has_children) {
        printf(")");
    }
}

int main() {
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

    print_expr(&ax);
    printf("\n");

    return 0;
}
