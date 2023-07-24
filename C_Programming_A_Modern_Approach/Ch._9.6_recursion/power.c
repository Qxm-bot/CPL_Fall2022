//
// Created by 25378 on 2022/11/3.
//
#include <stdio.h>

int power(int x, int n);
int main(void){
    int i = power(5, 3);
    printf("%d", i);

    return 0;
}

/*int power(int x, int n){
    if(n == 0){
        return 1;
    } else{
        return x * power(x, n - 1);
    }
}*/
int power(int x, int n){
    return n == 0 ? 1 : x * power(x, n - 1);
}