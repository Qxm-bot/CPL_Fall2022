//
// Created by 25378 on 2023/2/20.
//
#include <stdio.h>


int abs(int n);
int map[800][800] = {0};
int total[800][800] = {0};
int record[3600][2] = {0};
int main(void){
    int m = 0;
    int n = 0;
    int d = 0;
    scanf("%d%d%d", &n, &m, &d);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &map[d + i][d + j]);
        }
    }
    int v = 0;
    int vm = 0;
    for(int i = 2 * d + 1; i >= 1; i--){
        for(int j = 2 * d + 1; j >= 1; j--){
            if(abs(d + 1 - i) + abs(d + 1 - j) <= d){
                v += map[i][j];
            }
        }
    }
    total[1][1] = v;
    vm = v;

    for(int i = 1; i <= n; i++){
        int rec = 0;
        if(i % 2 == 1){
            for(int j = 2; j <= m; j++){
                int gap = 0;
                for(int k = 0; k <= d; k++){
                    gap -= map[d + i - k][d + j - d - 1 + k];
                }
                for(int k = 1; k <= d; k++){
                    gap -= map[d + i + k][d + j - d - 1 + k];
                }
                for(int k = 0; k <= d; k++){
                    gap += map[d + i - k][d + j + d - k];
                }
                for(int k = 1; k <= d; k++){
                    gap += map[d + i + k][d + j + d - k];
                }
                v = v + gap;
                total[i][j] = v;
                if(v > vm){
                    vm = v;
                }
            }
            rec = m;
        } else{
            for(int j = m - 1; j >= 1; j--){
                int gap = 0;
                for(int k = 0; k <= d; k++){
                    gap += map[d + i - k][d + j - d + k];
                }
                for(int k = 1; k <= d; k++){
                    gap += map[d + i + k][d + j - d + k];
                }
                for(int k = 0; k <= d; k++){
                    gap -= map[d + i - k][d + j + d + 1 - k];
                }
                for(int k = 1; k <= d; k++){
                    gap -= map[d + i + k][d + j + d + 1 - k];
                }
                v = v + gap;
                total[i][j] = v;
                if(v > vm){
                    vm = v;
                }
            }
            rec = 1;
        }
        if(i != n){
            int g = 0;
            for(int k = 0; k <= d; k++){
                g -= map[d + i - d + k][d + rec - k];
            }
            for(int k = 1; k <= d; k++){
                g -= map[d + i - d + k][d + rec + k];
            }
            for(int k = 0; k <= d; k++){
                g += map[d + i + d + 1 - k][d + rec - k];
            }
            for(int k = 1; k <= d; k++){
                g += map[d + i + d + 1 - k][d + rec + k];
            }
            v = v + g;
            total[i + 1][rec] = v;
            if(v > vm){
                vm = v;
            }
        }
    }

    int count = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(total[i][j] == vm){
                record[count][0] = i;
                record[count][1] = j;
                count++;
            }
        }
    }
    printf("%d %d\n", vm, count);
    for(int i = 0; i < count; i++){
        printf("%d %d\n", record[i][0], record[i][1]);
    }
    return 0;
}

int abs(int n){
    if(n >= 0){
        return n;
    } else{
        return -1 * n;
    }
}