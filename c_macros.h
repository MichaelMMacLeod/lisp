#ifndef INCLUDE_C_MACROS_H
#define INCLUDE_C_MACROS_H

// MAKE_P - create a function FN_NAME_p which tests if its param is equal to
// the result of SYMBOL's stringification
#define MAKE_P(FN_NAME, SYMBOL) \
    int FN_NAME ## _p(char *symbol) { \
        return strcmp(#SYMBOL, symbol) == 0; \
    }

#endif
