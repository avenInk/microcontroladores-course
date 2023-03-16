#include<stdio.h> 
#include<time.h>
#include<stdbool.h>

time_t seconds;

int hola = NULL;
long rest; 

int main(){
    seconds = time(NULL);
    rest = (seconds-(seconds/3600/24)*3600*24)/3600;
    printf("%ld", rest);
    printf("El número de días desde el inicio del conteo es de %ld", seconds/3600/24);
    printf("hoy es el año %ld, y son las %ld horas con %ld minutos",1970+seconds/3600/24/365, 1,1);

    return 0;
}