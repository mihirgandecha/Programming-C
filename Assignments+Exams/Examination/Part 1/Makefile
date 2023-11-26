CFLAGS := -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -Werror -g
SANI   := -g3 -fsanitize=address -fsanitize=undefined

part1: tr tr_s
	./tr
	./tr_s
	
tr: main1.c toprow.c
	gcc main1.c toprow.c $(FLGS) -O3 -o tr

tr_s: main1.c toprow.c toprow.h
	gcc main1.c toprow.c $(FLGS) $(SANI) -o tr_s

part2: sseq sseq_s
	./sseq
	./sseq_s

sseq: main2.c subseq.c subseq.h
	gcc main2.c subseq.c $(FLGS) -O3 -o sseq

sseq_s: main2.c subseq.c
	gcc main2.c subseq.c $(FLGS) $(SANI) -o sseq_s

all: part1 part2

clean: 
	rm -fr tr tr_s sseq sseq_s


