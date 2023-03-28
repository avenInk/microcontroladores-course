#include<stdio.h>

void func(int *var1, int *var2){
    *var1 = 10;
    *var2 = 30;
}


int origin1 = 0;
int origin2 = 0;
int *var1 = &origin1;

int main(void){

    func(&origin1, &origin2);

    printf("%d\n%d\n", origin1, origin2);
    printf("%d\n%d\n", var1, *var1);
    return 0;
}
