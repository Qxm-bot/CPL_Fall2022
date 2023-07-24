//
// Created by 25378 on 2022/10/28.
//
#include <stdio.h>

int main(void){
    int n = 0;
    int sequence[2000] = {0};
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        scanf("%d",&sequence[i]);
    }
    int m = 1;
    int mark = n - 1;
    while(sequence[mark] <= sequence[mark - 1]){
        mark = mark - 1;
        m++;
    }
    int min = 0;
    for (int j = n - m; j <= n - 1; j++){
        if(sequence[j] >= sequence[mark - 1]){
            min = sequence[j];
            break;
        }
    }
    int index = 0;
    for(int i = n - m; i <= n - 1; i++){
        if(sequence[i] >= sequence[mark - 1] && sequence[i] <= min){
            min = sequence[i];
            index = i;
        }
    }

    int mid = sequence[index];
    sequence[index] = sequence[mark - 1];
    sequence[mark - 1] = mid;

    int copy[2000] = {0};
    for (int i = 0; i < n; i++){
        copy[i] = sequence[i];
    }
    for(int i = n - m; i <= n - 1; i++){
        sequence[i] = copy[2 * n - m - 1 - i];
    }
    for(int i = 0; i < n; i++){
        printf("%d ",sequence[i]);
    }
    return 0;
}