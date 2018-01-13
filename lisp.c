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

/* Singly-linked list of Atoms. */
struct List {
    struct Atom* data;
    struct List* next;
};


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

/* Prints out a List in this form:
 *  (item1 item2 item3)
 */
void print_list(struct List* list) {
    if (list == NULL) {
        printf("()");

        return;
    }

    printf("(");

    loop {
        char str[MAX_SYMBOL_SIZE];
        atom_string(list->data, str);
        printf("%s", str);
        
        if (list->next == NULL) {
            break;
        } else {
            printf(" ");
            list = list->next;
        }
    }

    printf(")\n");
}

int main() {
    struct Atom a;
    a.type = BOOLEAN;
    a.boolean = 1;

    struct List node_a;
    node_a.data = &a;
    node_a.next = NULL;

    struct Atom b;
    b.type = INTEGER;
    b.integer = 9;

    struct List node_b;
    node_b.data = &b;
    node_b.next = &node_a;

    struct Atom c;
    c.type = SYMBOL;
    c.symbol = "Green";

    struct List node_c;
    node_c.data = &c;
    node_c.next = &node_b;

    print_list(&node_c);

    return 0;
}
