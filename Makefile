FILES = src/lisp.c src/types/node/node.h src/types/node/node_utils.h src/types/list/list.h src/functions/repl.h

$(shell [ -d build/debug ] || mkdir -p build/debug)
$(shell [ -d build/release ] || mkdir -p build/release)

debug: $(FILES)
	gcc -o build/debug/target -g -Wall $(FILES)

release: $(FILES)
	gcc -o build/release/target -O2 $(FILES)

clean:
	rm build/debug/target
	rm build/release/target
