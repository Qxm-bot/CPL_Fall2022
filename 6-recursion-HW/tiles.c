//
// Created by 25378 on 2022/11/4.
//
#include <stdio.h>
int num(int n);
int main(void){
    int n;
    scanf("%d", &n);
    printf("%d", num(n));
    return 0;
}
int num(int n){
    if(n == 1){
        return 1;
    }
    int plus[40] = {0};
    plus[1] = 1;
    plus[2] = 1;
    for(int i = 3; i < 40; i++){
        plus[i] = plus[i - 1] + plus[i - 2];
        if(i >= n - 1){
            break;
        }
    }
    return num(n - 1) + plus[n - 1];
}