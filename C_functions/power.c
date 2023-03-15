#include<stdio.h>

int power(int num, int power);

int main(void){
    printf("%d", power(3, 2));


    return 0;
}

int power(int num, int power){
    int result = 1;

    for (int i = 0; i<power; i++){
        result = result * num;

    }
    
    return result;
}