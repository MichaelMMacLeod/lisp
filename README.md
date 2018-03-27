### Compiling

```
$ gcc main.c
```

### Usage

Currently supports quote, list, head, and tail.
'symbol is a reader macro that maps to (quote symbol)

```
$ ./a.out
> (list (quote hello) 'world)
(HELLO WORLD)
> (head '(a b c))
A
> (tail '(a b c))
(B C)
```
