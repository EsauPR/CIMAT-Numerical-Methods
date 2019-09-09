.PHONY: build buildlib clean depend run valgrind help

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

# External libraries
LIBS = -lm

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

# Lib Location
IDIR = ../../src/include/

# Executable name
BIN = main

# Source code
SRC = ../../src/target/build
CC = gcc

# Object files from which $BIN depends
OBJS = ${SRC}/bwfw_substitution.o \
	${SRC}/gaussian_elimination.o \
	${SRC}/matrixio.o \
	${SRC}/matrix.o

## Compiles the executable program by default main.c
$(BIN): $(BIN).c buildlib
	$(CC) $(CFLAGS) $(DEFS) $(BIN).c ${OBJS} -o $(BIN) -I${IDIR} $(LIBS)

buildlib:
	cd ../../src && make && cd -

## Remove binaries and objects
clean:
	rm -f *~ *.o $(BIN)
	find ${SRC}/ -type f -name '*.o' -exec rm {} +

depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c

## Run the executable
run:
	./$(BIN) ${f1} ${f2}

## Run the executable with valgrind to check memory vulnerabiliies
valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(BIN) ${f1} ${f2}

help:
	@echo "$$(tput bold)Available rules:$$(tput sgr0)"
	@echo
	@sed -n -e "/^## / { \
	h; \
	s/.*//; \
	:doc" \
	-e "H; \
	n; \
	s/^## //; \
	t doc" \
	-e "s/:.*//; \
	G; \
	s/\\n## /---/; \
	s/\\n/ /g; \
	p; \
	}" ${MAKEFILE_LIST} \
	| LC_ALL='C' sort --ignore-case \
	| awk -F '---' \
	-v ncol=$$(tput cols) \
	-v indent=19 \
	-v col_on="$$(tput setaf 6)" \
	-v col_off="$$(tput sgr0)" \
	'{ \
	printf "%s%*s%s ", col_on, -indent, $$1, col_off; \
	n = split($$2, words, " "); \
	line_length = ncol - indent; \
	for (i = 1; i <= n; i++) { \
		line_length -= length(words[i]) + 1; \
		if (line_length <= 0) { \
		line_length = ncol - indent - length(words[i]) - 1; \
		printf "\n%*s ", -indent, " "; \
		} \
		printf "%s ", words[i]; \
	} \
	printf "\n"; \
	}' \
	| more $(shell test $(shell uname) = Darwin && echo '--no-init --raw-control-chars')
