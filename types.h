/* types.h
 *
 * Defines several types.
 *
 * typedefs
 *      Symbol
 *      Integer
 *      Node
 *      List
 */

#ifndef INCLUDE_TYPES_H
#define INCLUDE_TYPES_H

/* A '\0'-terminated string of length >= 1 that does not include whitespace 
 * characters.
 *
 * ex:
 *      Symbol s = "Hello";
 *      Symbol s = "+";
 *
 * wrong examples:
 *      Symbol s = "Hello world" // spaces aren't allowed
 *      Symbol s = ""            // length should be >= 1
 */
typedef char* Symbol;

typedef int Integer;

/* A value which can either be a Symbol or an Integer.
 * 
 * ex:
 *      int data = 9;
 *
 *      Node n;
 *      n.type = INTEGER;
 *      n.integer = &data;
 */
typedef struct {
    enum {
        SYMBOL,
        INTEGER
    } type;

    union {
        Symbol* symbol;
        Integer* integer;
    };
} Node;

/* A singly-linked list of Nodes.
 *
 * ex:
 *      List l;
 *      l.node = node;
 *      l.next = &next;
 */
typedef struct {
    Node node;
    Node* next;
} List;

#endif
