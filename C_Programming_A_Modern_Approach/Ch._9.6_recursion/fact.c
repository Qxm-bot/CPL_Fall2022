//
// Created by 25378 on 2022/11/3.
//
#include <stdio.h>
int fact(int n);
int main(void){
    int i = fact(3);
    printf("%d", i);

    return 0;
}

int fact(int n){
    if(n <= 1){
        return 1;
    } else{
        return n * fact(n - 1);
    }
}