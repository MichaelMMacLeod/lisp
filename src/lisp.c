#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions/repl.h"

int main() {
    while (1) {
        print(eval(read()));
    }

    return 0;
}
