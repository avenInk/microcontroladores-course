#include<stdio.h>

unsigned short estado = 2;

int main(void){
    switch (estado){
        case 0:
        printf("caso cero");
        break;
        case 1:
        printf("caso uno");
        break;
        case 2:
        printf("caso 2");
        break;
        default:
        printf("no se encunetra el caso seleccionado");
        break;
    }


    return 0;
}