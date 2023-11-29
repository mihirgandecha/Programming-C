# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal -Werror -g

# Optimizer flags
OPTFLAGS := -O3 # Optimize compiled code for execution speed

# Sanitizer flags
SANFLAGS := -fsanitize=address -fsanitize=undefined -g3 # Enable sanitizers for runtime error checking

# Source files
SRC := $(wildcard *.c)

# Object files (not used in this example, but kept for potential future use)
OBJ := $(SRC:.c=.o)

# Target executables
TARGET := $(SRC:.c=)

# Default target
all: $(TARGET)

# Generic rule for building executables
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Target for building with optimization flags
optimize: CFLAGS += $(OPTFLAGS)
optimize: $(TARGET)

# Target for building with sanitizer flags
sanitize: CFLAGS += $(SANFLAGS)
sanitize: $(TARGET)

# Clean target
clean:
	rm -f $(TARGET)

.PHONY: all optimize sanitize clean
