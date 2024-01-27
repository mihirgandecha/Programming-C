
//@Lws have been doing a few iterations of this func

// bool storeList(Program *turtle, int startList, int cList, int listLen){
//     int index = INDEX(*turtle->varTemp);
//     if(turtle->store[index].inUse == true){
//         ERROR("Variable already in use!");
//         return false;
//     }
//     for(int i = startList; i < cList; i++){
//         if(STRSAME(turtle->wds[startList], "{") || STRSAME(turtle->wds[startList], "{")){
//             startList++;
//             storeList(turtle, startList, cList, listLen);
//         }
//         strcpy(turtle->store[index].var, turtle->wds[startList]);
//         turtle->store[index].inUse = true;
//         if(Inslst(turtle) == false){
//             return false;
//         }
//         memset(turtle->store[index].var, 0, sizeof(turtle->store[index].var));
//         turtle->store[index].inUse = false;
//         if(startList != cList){
//             startList++;
//             storeList(turtle, startList, cList, listLen);
//         }
//         return true;
//     }
//     return false;
// }
// bool storeList(Program *turtle, int startList, int cList){
//     int index = INDEX(*turtle->varTemp);
//     for(int i = startList; i < cList; i++){
//         turtle->cw = i;
//         if(STRSAME(turtle->wds[i], "{") || STRSAME(turtle->wds[i], "\' '")){
//             storeList(turtle, startList, cList);
//         }
//         strcpy(turtle->store[index].var, turtle->wds[i]);
//         turtle->store[index].inUse = true;
//         if (Word(turtle) || Varnum(turtle)){
//             turtle->cw = cList;
//             if(!Inslst(turtle)){
//                 turtle->store[index].inUse = false;
//                 return false;
//             }
//         }
//         turtle->store[index].inUse = false;
//     }
//     return true;
// }

//@Lws function is attempting to save whatever is in Loop {}, inside my store, so that if an instruction like FORWARD $C, it interps first->last element recursively
//Was struggling with how to use with stack without affecting PFIX


// bool setList(Program *turtle){
//     //find start and end of loop
//     stacktype start = "{";
//     stacktype c;
//     stack_peek(turtle->s, &c);
//     if(!(STRSAME(c, start))){
//         return false;
//     }
//     //find its pair
//     int endP;
//     endP = findEnd(turtle);     
//     //Making sure stack is in right place:
//     if(turtle->s->size > 0){
//         if(!(STRSAME(turtle->s->start->i, "{") && STRSAME(turtle->s->end->i, "}"))){
//             return false;
//         }
//     }
//     if(!(processLoop(turtle, endP))){
//         return false;
//     }
//     return true;
// }

// bool processLoop(Program *turtle, int endP){
//     for(int i = 0; i <= endP; i++){
//         int index = INDEX(*turtle->varTemp);
//         stacktype d;
//         stack_peek(turtle->s, &d);
//         strcpy(turtle->store[index].var, d);
//         if (turtle->s->size > 0 && (Word(turtle) || Varnum(turtle))){
//             if(Inslst(turtle)){
//                 queue_pop(turtle->s, &d);
//                 turtle->store[index].inUse = false;
//             }
//             if(turtle->s->size == 0){
//                 return true;
//             }
//         }
//         return setList(turtle);
//     }
//     return false;
// }

// int findEnd(Program *turtle){
//     int startP = 0;
//     //find its pair
//     int endP;
//     while (startP <= turtle->s->size){
//         stacktype end = "}";
//         stacktype d;
//         stack_peek(turtle->s, &d);
//         if STRSAME(d, end){
//             endP = startP;
//             return endP;
//         }
//         startP++;
//     }
//     return 1;
// }

//     for(int i = startList; i < cList; i++){
//         turtle->cw = startList;
//         if(STRSAME(turtle->wds[startList], "{") || STRSAME(turtle->wds[startList], "\' '")){
//             startList++;
//             storeList(turtle, startList, cList);
//         }
//         stacktype d;
//         stack_peek(turtle->s, &d);
//         strcpy(turtle->store[index].var, d);
//         turtle->store[index].inUse = true;
//         if (turtle->s->size > 0 && (Word(turtle) || Varnum(turtle))){
//             turtle->cw = cList;
//             Inslst(turtle);
//             queue_pop(turtle->s, &d);
//             turtle->store[index].inUse = false;
//             startList++;
//         }
//     }
//     return;
// }

bool storeList(Program *turtle, int startList, int cList){
    int index = INDEX(*turtle->varTemp);
    //startList is '{' and cList is '}'
    for(int i = cList - 1; i >= startList; i--){
        //resetting cw to where '{' is
        turtle->cw = i;
        //first checking if it is { OR }
        if(!STRSAME(turtle->wds[i], "{") && !STRSAME(turtle->wds[i], "}")){
            //looping through the list {}
            strcpy(turtle->store[index].var, turtle->wds[i]);
            //setting the store to be true (array of struct)
            turtle->store[index].inUse = true;
            if (Word(turtle) || Varnum(turtle)){
                //setting cw to where it originally was
                turtle->cw = cList;
                if(!Inslst(turtle)){
                    //before recursive call resetting the store.
                    turtle->store[index].inUse = false;
                    return false;
                }
            }
        turtle->store[index].inUse = false;
        }
    }
    return true;
}

bool storeList(Program *turtle, int startList, int cList){
    int index = INDEX(*turtle->varTemp);
    //startList is '{' and cList is '}'
    for(int i = cList - 1; i >= startList; i--){
        //resetting cw to where '{' is
        turtle->cw = i;
        //first checking if it is { OR }
        if(!STRSAME(turtle->wds[i], "{") && !STRSAME(turtle->wds[i], "}")){
            //looping through the list {}
            strcpy(turtle->store[index].var, turtle->wds[i]);
            //setting the store to be true (array of struct)
            turtle->store[index].inUse = true;
            if (Word(turtle) || Varnum(turtle)){
                //setting cw to where it originally was
                turtle->cw = cList;
                if(!Inslst(turtle)){
                    //before recursive call resetting the store.
                    turtle->store[index].inUse = false;
                    return false;
                }
            }
        turtle->store[index].inUse = false;
        }
    }
    return true;
}