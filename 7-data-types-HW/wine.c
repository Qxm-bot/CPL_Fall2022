//
// Created by 25378 on 2022/11/11.
//
#include <stdio.h>

void calculate(int value[],int limit[], int n, int L);
int max_of_value = 0;
int main(void){
    int n = 0;
    int L = 0;
    int value[10000] = {0};
    int limit[10000] = {0};
    scanf("%d%d", &n, &L);
    for(int i = 0; i < n; i++){
        scanf("%d", &value[i]);
    }
    for(int i = 0; i < n; i++){
        scanf("%d", &limit[i]);
    }
    calculate(value, limit, n, L);
    printf("%d", max_of_value);

    return 0;
}

void calculate(int value[], int limit[], int n, int L){
    int max = value[0];
    int mark = 0;
    for(int i = 1; i < n; i++){
        if(value[i] > max){
            max = value[i];
            mark = i;
        }
    }
    if(limit[mark] >= L){
        max_of_value += value[mark] * L;
    } else if(limit[mark] < L){
        L = L - limit[mark];
        max_of_value += value[mark] * limit[mark];
        if(mark != n - 1) {
            for (int i = mark; i < n; i++) {
                value[i] = value[i + 1];
                limit[i] = limit[i + 1];
            }
        }
        calculate(value, limit, n - 1, L);
    }
}