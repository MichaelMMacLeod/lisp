### Compiling

```
$ gcc main.c
```

### Usage

Currently supports the following:

```
- quote (and a ' reader macro)
- list operations
    - list
    - head
    - tail
- eq (pointer equality)
- defvar
- lambda
    - Introduces a new lexical scope. Lexical bindings can shadow global ones
      defined with defvar.
```

```
$ ./a.out
> (list (quote hello) 'world)
(HELLO WORLD)
> (head '(a b c))
A
> (tail '(a b c))
(B C)
> (defvar a 'hello)
A
> (defvar b 'world)
B
> (eq a b)
NIL
> (eq 'hello a)
T
> ((lambda (a b) (list b a)) 'second 'first)
(FIRST SECOND)
```
