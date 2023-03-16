#include<stdio.h>

int n, hola[30], i; 

int main(void){
    printf("Ingresa el número a comvertir: ");
    scanf("%d", &n);
    for(i = 0; n>0; i++){
        hola[i] = n%2;
        n = n/2;
    }
    for(i = i-1; i>=0; i--)
    printf("%d", hola[i]);
    return 0;
}