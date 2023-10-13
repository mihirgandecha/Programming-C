#include <stdio.h>
#include <assert.h>

int button_press(int t);


int main(void){


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

return 0;
}

int button_press(int t){ 

    struct Button {
        char button_name[25];
        int time_in_seconds;
        int button_counter;
    };

    struct Button ten_min = {"Ten Minute Button", 600, 0};
    struct Button one_min = {"One Minute Button", 60, 0};
    struct Button ten_sec = {"Ten Second Button", 10, 0};
    
    //Decision Tree One
    while (t >= ten_min.time_in_seconds){
        t -= ten_min.time_in_seconds;
        ten_min.button_counter++;
    } 

    //Decision Tree Two
    while (t >= one_min.time_in_seconds){
        t -= one_min.time_in_seconds;
        one_min.button_counter++;
    }

    //Decision Tree Three

    while (t >= ten_sec.time_in_seconds){
        t -= ten_sec.time_in_seconds;
        ten_sec.button_counter++;
    }

    if (t > 0){
        ten_sec.button_counter++;
    }


    int result = ten_min.button_counter + one_min.button_counter + ten_sec.button_counter; 
    return result;
    }

    void test(void){
        assert(button_press(25) == 3);
        assert(button_press(90) == 4);
        assert(button_press(705) == 7);
    }

