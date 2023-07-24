//
// Created by 25378 on 2022/11/4.
//
#include <stdio.h>
int find(int x);
int a[100001] = {0};
int main(void){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++){
        printf("%d ", find(i));
    }

    return 0;
}

int find(int x){
    if(a[x] == x){
        return x;
    } else{
        return find(a[x]);
    }
}