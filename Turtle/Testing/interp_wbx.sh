#!/bin/bash

TTL_FILES=("5x5.ttl" "forward.ttl" "my_fwd.ttl" "turn.ttl" "donothing.ttl" "hypno.ttl" "nested.ttl" "set1.ttl" "downarrow.ttl" "Interpreter" "octagon1.ttl" "set2.ttl" "empty.ttl" "labyrinth.ttl" "octagon2.ttl" "spiral.ttl" "fail_parse_ok_interp.ttl" "loopbasic.ttl" "ok_parse_fail_interp.ttl" "tunnel.ttl")

for ttl_file in "${TTL_FILES[@]}"; do
    make combined
    ./combined_target "TTLs/$ttl_file"
    echo "Press any key to continue..."
    read -n 1
done
