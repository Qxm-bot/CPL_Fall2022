//
// Created by 25378 on 2022/10/28.
//
#include <stdio.h>
#include <math.h>

int main(void){
    int n = 0;
    int t = 0;

    int Sum(int n,int t);

    scanf("%d %d",&n,&t);

    int total = 0;

    for(int i = 1; i <= n; i++){
        total = total + Sum(i,t);
    }
    printf("%d",total);

    return 0;
}

int Sum(int n,int t){
    int sum = 0;
    for(int i = 0; i < n ; i++){
        sum = sum + t * pow(10.0, i);
    }
    return sum;
}