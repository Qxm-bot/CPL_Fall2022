//
// Created by 25378 on 2022/12/23.
//
#include <stdio.h>

int main(void){
    int dmg[10000] = {0};
    int type[10000] = {0};
    int total_dmg[10000] = {0};
    int n = 0;
    int m = 0;
    int k = 0;
    int max_dmg = 0;
    scanf("%d%d%d", &n, &m, &k);

    for(int i = 0; i < n; i++){
        scanf("%d%d", &dmg[i], &type[i]);
        if(type[i]){
            total_dmg[i] = dmg[i] * (m + 1);
        } else{
            total_dmg[i] = dmg[i];
        }
    }

    for(int i = 1; i < n; i++){
        for(int j = n - 1; j >= i; j--){
            if(total_dmg[j] > total_dmg[j - 1]){
                int exchange = total_dmg[j];
                total_dmg[j] = total_dmg[j - 1];
                total_dmg[j - 1] = exchange;
            }
        }
    }

    for(int i = 0; i < k; i++){
        max_dmg += total_dmg[i];
    }

    printf("%d", max_dmg);

    return 0;
}