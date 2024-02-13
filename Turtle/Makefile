CC=gcc 
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
TEST = -DRUN_TESTS

# Give permission to all files using chmod first
permissions:
	@chmod 777 -R ./

all: parse_s interp_s

parse_s: Parse/parse.h Parse/parse.c
	$(CC) Parse/parse.c -o parse_s -I./Parse $(SANITIZE) -lm

#Main test for parser command:
run_parsetest:
	chmod +x ./Testing/parsetest.sh
	./Testing/parsetest.sh

interp_s: Interp/interp.h Interp/interp.c neillsimplescreen.c neillsimplescreen.h
	$(CC) neillsimplescreen.c Interp/interp.c -o interp_s -I./Interp $(SANITIZE) -lm

extension_s: Extension/extension.h Extension/extension.c neillsimplescreen.c neillsimplescreen.h
	$(CC) neillsimplescreen.c Extension/extension.c -o extension_s -I./Extension $(SANITIZE) -lm

test_interp: Interp/interp.h Interp/interp.c neillsimplescreen.c neillsimplescreen.h
	$(CC) $(TEST) neillsimplescreen.c Interp/interp.c -o interp_s -I./Interp $(SANITIZE) -lm

test: interp_s
	./interp_s TTLs/octagon2.ttl 

combined: Interp/interp.h Interp/interp.c neillsimplescreen.c neillsimplescreen.h Interp/Stack/specific.h Interp/Stack/linked.c Interp/general/general.h Interp/general/general.c
	$(CC) -g neillsimplescreen.c Interp/interp.c Interp/Stack/linked.c Interp/general/general.c -o combined_target -I./Interp/Stack $(SANITIZE) -lm

# Uncomment as you test for different .ttl files
runcom: clean combined
#	./combined_target TTLs/empty.ttl 
# ./combined_target TTLs/forward.ttl 
# ./combined_target TTLs/5x5.ttl 
# 	./combined_target TTLs/octagon1.ttl 
# ./combined_target TTLs/octagon2.ttl
# ./combined_target TTLs/my_fwd.ttl 
# ./combined_target TTLs/downarrow.ttl 
# ./combined_target TTLs/fail_parse_ok_interp.ttl 
# ./combined_target TTLs/hypno.ttl 
# ./combined_target TTLs/labyrinth.ttl 
# ./combined_target TTLs/loopbasic.ttl 
# ./combined_target TTLs/nested.ttl 
# ./combined_target TTLs/set1.ttl 
# ./combined_target TTLs/set2.ttl 
 ./combined_target TTLs/spiral.ttl 
# ./combined_target TTLs/tunnel.ttl 
# ./combined_target TTLs/turn.ttl 

runcom_txt: combined
	./combined_target TTLs/donothing.ttl f_outf_out.txt
# ./combined_target TTLs/empty.ttl f_out.txt
# ./combined_target TTLs/forward.ttl f_out.txt
# ./combined_target TTLs/5x5.ttl f_out.txt
# ./combined_target TTLs/octagon1.ttl f_out.txt
# ./combined_target TTLs/octagon2.ttl f_out.txt
# ./combined_target TTLs/my_fwd.ttl f_out.txt
# ./combined_target TTLs/downarrow.ttl f_out.txt
# ./combined_target TTLs/fail_parse_ok_interp.ttl f_out.txt
# ./combined_target TTLs/hypno.ttl f_out.txt
# ./combined_target TTLs/labyrinth.ttl f_out.txt
# ./combined_target TTLs/loopbasic.ttl f_out.txt
# ./combined_target TTLs/nested.ttl f_out.txt
# ./combined_target TTLs/set1.ttl f_out.txt
# ./combined_target TTLs/set2.ttl f_out.txt
# ./combined_target TTLs/spiral.ttl f_out.txt
# ./combined_target TTLs/tunnel.ttl f_out.txt
# ./combined_target TTLs/turn.ttl f_out.txt

#Included in Parse script
parse_assert: Parse/parse.h Testing/parse_withtest.c Testing/parse_test.c
	$(CC) Testing/parse_withtest.c Testing/parse_test.c -g -o parse_withtest -I./Parse -I./Testing -lm
	./parse_withtest

run_parseTTLs: parse_s	
	./parse_s TTLs/empty.ttl
	./parse_s TTLs/forward.ttl
	./parse_s TTLs/ok_parse_fail_interp.ttl
	./parse_s TTLs/set1.ttl
	./parse_s TTLs/donothing.ttl
	./parse_s TTLs/set2.ttl
	./parse_s TTLs/turn.ttl
	./parse_s TTLs/spiral.ttl
	./parse_s TTLs/octagon1.ttl
	./parse_s TTLs/octagon2.ttl
	./parse_s TTLs/tunnel.ttl
	./parse_s TTLs/labyrinth.ttl
	./parse_s TTLs/hypno.ttl
	./parse_s TTLs/5x5.ttl
	./parse_s TTLs/downarrow.ttl

clean:
	rm -f Turtle.zip parse_s parse_test parse_withtest combined_target interp_s out_*.txt out_*.ps out_*.pdf

zip:
	zip -r Turtle.zip .

