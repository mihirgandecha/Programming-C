#include "parse.h"

int main(int argc, char* argv[]){
    if(argc != 3){
        ERROR("Error on argv[0]\n");
        exit(EXIT_FAILURE);
    }
    FILE* fttl = fopen(argv[1], "r");
    if(!fttl){
        ERROR("Cannot read from argv[1] \n");
        fclose(fttl);
        exit(EXIT_FAILURE);
    }
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        fclose(fttl);
        exit(EXIT_FAILURE);
    }
    while((turtle->cmnd[turtle->cmnd] = fgetc(fttl)) != EOF){
        turtle->cw++;
    }
    printf("Parsed OK\n");
    fclose(fttl);

    Prog(turtle);

    free(turtle);
    return 0;
}

bool Prog(Program *turtle){
    if (scanf("%s", turtle->cmnd[turtle->cw]) != 1 || !strsame(turtle->cmnd[turtle->cw], "START")){
        ERROR("No 'START' statement!\n");
        return false;
    }
    return true;
}

// bool Inslst(Program *turtle){
//     turtle->endReached = false;
//     //Prog done
//     while (turtle->cw < MAXCMND - 1 && !turtle->endReached){
//         turtle->cw++;
//         if (scanf("%s", turtle->cmnd[turtle->cw]) != 1){
//             ERROR("Failed to read command.\n");
//             return false;
//         }
//         Inslst(turtle);
//     }
//     return true;
// }