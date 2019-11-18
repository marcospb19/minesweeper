# Final program name
PROGRAM = campominado

# Default target and pseudo-targets
.DEFAULT_GOAL = $(PROGRAM)
.PHONY = clean
.PHONY = install

# Compiler, Compilation flags, link flags
CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11
LDFLAGS = -lm -lncurses

# Object files to be built
# OBJECTS = teste.o
OBJECTS = main.o mapa.o jogo.o


$(PROGRAM): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(PROGRAM) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm $(OBJECTS) 2> /dev/null || exit 0
