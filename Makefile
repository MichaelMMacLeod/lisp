FILES = src/lisp.c src/types/node/node.h src/types/node/node_utils.h src/types/tree/tree.h src/types/tree/tree_utils.h

target.o: $(FILES)
	gcc -o build/lisp.o $(FILES)