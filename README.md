### Compiling

```
$ gcc main.c
```

### Usage

```
- QUOTE
    - (quote arg)
    - with a reader macro:
        - 'arg
- LIST
    - (list args ...)
- HEAD
    - (head list-form)
- TAIL
    - (tail list-form)
- EQ
    - (eq symbol1 symbol2)
- DEFVAR
    - (defvar symbol-name form)
- LAMBDA
    - (lambda (args ...) body-form)
    - can be used with defvar to create named functions:
        - (defvar symbol-name (lambda (args ...) body-form))
- CREATE-MAP
    - (create-map)
- GET
    - (get symbol map)
- SET
    - (set (get symbol map) new-value map)
- READ
    - read from standard input:
        - (read)
    - read from string:
        - (read "a string")
- EVAL
    - (eval form)
- LOOP
    - infinite loop:
        - (loop form)
- PRINT
    - (print form)
```
