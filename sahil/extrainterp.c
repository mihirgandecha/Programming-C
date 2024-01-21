    // int cw = turtle->cw;
    // int temp = 0;
    // //TODO First in first out
    // for (int i = turtle->s->size; i >= 1; i--){
    //     stacktype d;
    //     stack_pop(turtle->s, &d);
    //     int len = strlen(d);
    //     if(len > 1){
    //         memmove(&turtle->wds[cw + 1], &turtle->wds[cw], (MAXCMND - cw - 1) * sizeof(turtle->wds[0]));
    //         strncpy(turtle->wds[cw], d, MAXTOKENSIZE);
    //         if(Word(turtle)){
    //             temp += 2;
    //             memmove(&turtle->wds[cw + 1], &turtle->wds[cw], (MAXCMND - cw - 1) * sizeof(turtle->wds[0]));
    //             strncpy(turtle->wds[cw], "COLOUR", MAXTOKENSIZE);
                
    //         }
    //     }
    //     turtle->cw = cw;
    //     Inslst(turtle);
    //     cw = cw + temp;
    //     temp = 0;
    //         // Copy d into turtle->wds[cw].
    //         // free(d);
        
    //     // free(d);
    //     // if(df != NULL){
    //     //     // Use df->i, df->loopIndex, and df->instruction as needed.
    //     //     // This will depend on the specifics of your program.
    //     //     Inslst(turtle);
    //     //     free(df);
    //     // }
    // //TODO remove after for oct2:
    // // assert(turtle->loopItems[turtle->loopIndx] == 8);
    // //TODO remove after for labrin:
    // // assert(turtle->loopItems[2] == 4);
    // // assert(turtle->loopItems[3] == 12);
    // }


bool Loop(Program *turtle){
    if (!STRSAME(turtle->wds[turtle->cw], "LOOP")){
        return false;
    }
    turtle->cw++;
    if (!Ltr(turtle)){
        return false;
    }
    turtle->loopIndx = INDEX(turtle->wds[turtle->cw][0]);
    assert(turtle->s->start == NULL);
    stacktype d = &turtle->wds[turtle->cw][0];
    stack_push(turtle->s, d);  
    
    // turtle->s->loopIndex = INDEX(turtle->wds[turtle->cw][0]);
    //Wrong placement needs to be under next!
    // turtle->s->loopIndex = INDEX(turtle->wds[turtle->cw][0]); 
    // stack* s = NULL;
    // initStack(s, turtle);
    turtle->cw++;
    if (!STRSAME(turtle->wds[turtle->cw], "OVER")){
        return false;
    }
    turtle->cw++;
    turtle->loopItems[turtle->loopIndx] = 0;
    if (!Lst(turtle)){
        return false;
    }
    while(turtle->s->size > 0){
        d = stack_peek(turtle->s, &d);
        pop_stack(turtle->s)
        //while turtle.store[index].cw > 0
            //cwMax = turtle.store[index].cw
            //int tempCw = 0
            //set d -> turtle.store[index].var[cw]
            //insert a SET d ( turtle.store[index].var[cw] )-> turtle->wds[turtle->cw]
            //using memmove placing this instruction in cw and incrementing list and cw by 1
            //Execute: 
        if (!Inslst(turtle)){
            return false;
        }
            //After execution:
            //if tempCw <= cwMax
                //cw++
                //recursively call this function again.
            //else if tempCw > cwMax 
                //return true
    }