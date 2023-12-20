CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

TTL_DIR = /TTLs
TTL_FILES = $(wildcard $(TTL_DIR)/*.ttl)

all: parse_s #interp_s

parse_s: Parse/parse.h Parse/parse.c
	$(CC) Parse/parse.c -g -o parse_s -I./Parse $(SANITIZE) -lm

parse_with_test: Parse/parse.h Parse/parse.c Testing/parse_test.c
	$(CC) Parse/parse.c Testing/parse_test.c -g -o parse_test -I./Parse -I./Testing $(SANITIZE) -lm

# interp_s: Interp/interp.h Interp/interp.c neillsimplescreen.c neillsimplescreen.h
# 	$(CC) neillsimplescreen.c Interp/interp.c -o interp_s -I./Interp $(SANITIZE) -lm

### An example : you may wish to adapt this slightly
extension_s: Extension/extension.h Extension/extension.c neillsimplescreen.c neillsimplescreen.h
	$(CC) neillsimplescreen.c Extension/extension.c -o extension_s -I./Extension $(SANITIZE) -lm

runtest: parse_with_test
	./parse_test

run: parse_s
	./parse_s $(TTL_FILES)

clean:
	rm -f parse_s parse_test interp_s out_*.txt out_*.ps out_*.pdf