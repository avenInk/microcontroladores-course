#include<stdio.h>
#include <string.h>

void strrev(char* str);

int main(void){
    char string1[20] = "hola";
    printf("Escribe una frase \n");
    fgets(string1, 20, stdin);
    strrev(string1);
    printf("El string al reves es: %s\n", string1);
}

void strrev(char* str) {
    int i = 0, j = strlen(str) - 1;
    char temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}