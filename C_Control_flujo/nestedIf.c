#include<stdio.h>

int opt1, opt2 = 0;

int main(void){
    if(opt1 == 0){
        if (opt2 == 0){
            printf("Has elegido la opción 1");
        }
        if (opt2 == 1){
            printf("Has elegido la opción 2");
        }
        if (opt2 == 2){
            printf("Has elegido la opción 3");
        }
    }else if (opt1 == 2){
                if (opt2 == 0){
            printf("Has elegido la opción 1 2");
        }
        if (opt2 == 1){
            printf("Has elegido la opción 2 2");
        }
        if (opt2 == 2){
            printf("Has elegido la opción 3 2");
        }
    } 
    return 0;
}