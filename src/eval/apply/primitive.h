#ifndef INCLUDE_APPLY_PRIMITIVE_H
#define INCLUDE_APPLY_PRIMITIVE_H

struct sexpr *apply_primitive(char *p, struct list *args, struct map *package) {
    if (STR_EQ("QUOTE", p))
        return quote(args, package);

    if (STR_EQ("LIST", p))
        return list(args, package);

    if (STR_EQ("HEAD", p))
        return head(args, package);

    if (STR_EQ("TAIL", p))
        return tail(args, package);

    if (STR_EQ("LAMBDA", p))
        return lambda(args, package);

    if (STR_EQ("DEFVAR", p))
        return defvar(args, package);

    if (STR_EQ("EQ", p))
        return eq(args, package);

    return NULL;
}

#endif
