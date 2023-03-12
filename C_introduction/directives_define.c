#include<stdio.h>

#define PAPERCOST 15.30

int main(void){
    int compras = 20;
    float total_compras = 0;

    total_compras = compras * PAPERCOST;

    printf("Costo total = %f \n", total_compras);

    return 0;
}