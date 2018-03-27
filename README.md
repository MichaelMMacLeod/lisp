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
```

```
$ ./a.out
> (list (quote hello) 'world)
(HELLO WORLD)
> (head '(a b c))
A
> (tail '(a b c))
(B C)
```
