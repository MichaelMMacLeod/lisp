FILES = src/lisp.c src/types/node/node.h src/types/node/node_utils.h src/types/tree/tree.h src/types/tree/tree_utils.h src/functions/functions.h

debug: $(FILES)
	gcc -o build/debug/target -g $(FILES)

release: $(FILES)
	gcc -o build/release/target -O2 $(FILES)

clean:
	rm build/debug/target
	rm build/release/target
