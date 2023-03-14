#include<stdio.h>
#include<stdbool.h>

unsigned short variable = 0;

bool election = true;

int main(void){
    while(election){
        variable ++;
        printf("hola\n");
        if (!(variable < 10)){
            election = false;
        }
    }
    do {
        printf("hola, esto no tendrías que verlo, al menos en un while, pero esto es un do while 🤑");
    }while(election); //Election contiene un "false" dentro.

    for(unsigned short i = 1; i<200; i++){
        if (i == 3){
            continue; //3 no debe aparecer.
        }
        printf("   %d", i);
    }

    return 0;
}