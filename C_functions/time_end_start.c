#include<stdio.h> 
#include<time.h>

time_t start, end;


int main(){
    start = time(NULL);

    for (int i = 0; i<6147480; i++){
        printf("hola");
    }
    end = time(NULL);
    
    printf("El tempo de ejecución ha sido de %ld segundos", end-start);
    return 0;
}