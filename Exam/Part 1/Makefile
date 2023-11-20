# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -pedantic -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -O2

# Executable name
EXEC = part1

# Default target
all: $(EXEC)

# Compile question1.c into an executable
$(EXEC): part1.c
	$(CC) $(CFLAGS) part1.c -o $(EXEC)

# Clean up
clean:
	rm -f $(EXEC)

