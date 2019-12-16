.PHONY: build clean depend

# Headers
IDIR = ./include/

CC = g++

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g -I${IDIR} -fopenmp

# External libraries
LIBS = -lm

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

LIBDIR = ./lib

DEPS1 = $(shell find ${LIBDIR} -type f -name '*.c' | sed "s/\.c/\.o/")

OBJS = ${DEPS1}
TARGET = ./target/build
LIBNAME = ${TARGET}/libnumsys

## Compiles the executable program by default main.c
build: ${OBJS}
	mkdir -p ${TARGET}
	ar rcs $(LIBNAME).a $(shell find ${LIBDIR} -type f -name '*.o')


# This rule compiles each module into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@


## Remove binaries and objects
clean:
	find ${LIBDIR}/ -type f -name '*.o' -exec rm {} +
	find ${TARGET}/ -type f -name '*.so' -exec rm {} +
	find ${TARGET}/ -type f -name '*.a' -exec rm {} +


depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c
