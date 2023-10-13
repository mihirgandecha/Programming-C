#include <stdio.h>
#include <assert.h>

int button_press(int t);


int main(void){

    struct Button {
        char button_name[25];
        int time_in_seconds;
        int button_counter;
    };

    struct Button ten_min = {"Ten Minute Button", 600, 0};
    struct Button one_min = {"One Minute Button", 60, 0};
    struct Button ten_sec = {"Ten Second Button", 10, 0};

    //User Input
    int time_in;

    //sort out:
    printf("Type the time required in seconds: \n");
    if(scanf("%i", &time_in) != 1){
        printf("Invalid input!");
        return 1;
    }
    int result = button_press(time_in);
    printf("Number of button presses = %i\n ", result);

}

int button_press(int t){ 

    //Decision Tree One
    int i = ten_min.button_counter;
    int ten_duration = ten_min.time_in_seconds;

    while (t > ten_duration){
        i++;
        t -= ten_duration;
    }


    
    // for (int i; t > i; i++){
    //     t -= ten_duration;
        return t;
    }




//     return button_press;
// }