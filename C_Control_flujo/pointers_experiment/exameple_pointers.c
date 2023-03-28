#include<stdio.h>

int buenas = 40;
int *add = &buenas;

int main(void){
    printf("%d\n%d\n%d\n", &buenas, add, buenas);

    return 0;
}