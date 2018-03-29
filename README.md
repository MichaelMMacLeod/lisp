### Compiling

```
$ gcc main.c
```

### Usage

```
- quote 
    > (quote hello-world)
    HELLO-WORLD
    > 'reader-macro-also
    READER-MACRO-ALSO
- list
    > (list 'a 'b 'c)
    (A B C)
- head 
    > (head '(a b c))
    A
- tail
    > (tail '(a b c))
    (B C)
- eq
    > (eq 'hello 'hello)
    T
    > (eq 'hello 'world)
    NIL
- lambda
    > ((lambda (a b) (list b a)) 'first 'second)
    (SECOND FIRST)
- defvar
    > (defvar my-var 'hello-world)
    MY-VAR
    > (defvar get-my-var (lambda () my-var))
    GET-MY-VAR
    > (get-my-var)
    HELLO-WORLD
    > (defvar my-var 'hi-there)
    MY-VAR
    > (get-my-var)
    HI-THERE
```
