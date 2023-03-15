#include<stdio.h>

void n_for(int n);

int main(void){
    int n = 3;
    for (n; n>0; n--){
        printf("%d", n);
    }
    printf("%d\n\n", n);
    
    n = 3;
    n_for(n);
    printf("%d\n\n", n);
    return 0;
}

void n_for(int n){
    for (n; n>0; n-- ){
        printf("%d", n);
    }
}