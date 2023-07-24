//
// Created by 25378 on 2022/11/4.
//
#include <stdio.h>
int combination(int a, int b);
int main(void){
    int a = 0;
    int b = 0;
    scanf("%d%d", &a, &b);

    printf("%d", combination(a - 1, b - 1));

    return 0;
}

int combination(int a, int b){
    if(a == b){
        return 1;
    }
    if(b == 0){
        return 1;
    }
    return (combination(a - 1, b - 1) + combination(a - 1, b));
}