.PHONY: build

# Headers
IDIR = ./include/

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g -I${IDIR}

# External libraries
LIBS = -lm

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

LIBDIR = ./lib

# # Object files from which $BIN depends
# OBJSDIR1 = ${LIBDIR}/matrix
# DEPS1 = matrixio.o \
# 	   matrix.o
# OBJS1 =  $(patsubst %,$(OBJSDIR1)/%,$(DEPS1))

DEPS1 = $(shell find ${LIBDIR} -type f -name '*.c' | sed "s/\.c/\.o/")

OBJS = ${DEPS1}
TARGET = "./target/build"


## Compiles the executable program by default main.c
build: $(OBJS)
	mkdir -p ${TARGET}
	find ${LIBDIR} -type f -name '*.o' -exec cp {} ${TARGET} \;


# This rule compiles each module into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@


## Remove binaries and objects
clean:
	find ${LIBDIR}/ -type f -name '*.o' -exec rm {} +
	find ${TARGET}/ -type f -name '*.o' -exec rm {} +


depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c
