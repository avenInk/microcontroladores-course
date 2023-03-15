#include<stdio.h>

int add(int a, int b);

int main(void){
    
    printf("%d", add(100,100));
    
    return 0;
}

int add(int a, int b){
    return a+b;
}