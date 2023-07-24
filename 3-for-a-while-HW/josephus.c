//
// Created by 25378 on 2022/10/14.
//
#include <stdio.h>

int main(void)
{
    int n,k;

    scanf("%d %d",&n,&k);

    int live_or_dead[501] = {0};

    for(int i = 1; i <= n; i++){
        live_or_dead[i] = i;
    }

    int num = 1, sum = 0;

    int cns = n;

    while(sum != cns - 1){
        int t = num + k;
        while(t > n){
            t = t - n;
        }
        if(t != 1) {
            for (int i = t; i <= n; i++) {
                live_or_dead[i - 1] = live_or_dead[i];
            }
        }
        num = num + k;
        while(num > n){
            num = num - n;
        }
        if(num != 1) {
            num = num - 1;
        }
        n--;
        sum++;
    }

    printf("%d",live_or_dead[1]);

    return 0;
}