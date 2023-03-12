#include<stdio.h>

enum days{lunes, martes, miercoles, jueves, viernes, sábado, domingo} today;

enum deck{
    pica = 10,
    rey = 20,
    moke = 60,
} card;

int main(void){
    today = martes;
    printf("day %d" , today+1);

    card = moke;

    printf("\n\n%d", card);

    return 0;
}