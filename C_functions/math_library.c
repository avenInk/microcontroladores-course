#include<stdio.h>
#include <math.h>


int x;
double result;

int main(void){
    printf("Ingresa el valor de x: ");
    scanf("%d", &x);
    printf("el valor ingresado es: %d\n", x);
    result = sin(x);
    printf("El valor de seno es de: %f", result);
    return 0;
}