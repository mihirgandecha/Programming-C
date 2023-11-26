# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -pedantic -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -O2

# Executable name
EXEC = part2

# Default target
all: $(EXEC)

# Compile question1.c into an executable
$(EXEC): part2.c
	$(CC) $(CFLAGS) part2.c -o $(EXEC)

# Clean up
clean:
	rm -f $(EXEC)

