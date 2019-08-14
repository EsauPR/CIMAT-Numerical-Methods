# Makefile

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -g

# External libraries: only math in this example
LIBS = -lm

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

# The final executable program file, i.e. name of our program
BIN = main

# Object files from which $BIN depends
OBJS = ../../src/linear_equations_systems_solutions/backward_substitution.o \
	../../src/matrix.o

# This default rule compiles the executable program
$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(LIBS) $(OBJS) $(BIN).c -o $(BIN)

# This rule compiles each module into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
	find ../../src/ -type f -name '*.o' -exec rm {} +

depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c

run:
	./$(BIN)
