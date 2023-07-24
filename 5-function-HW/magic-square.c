//
// Created by 25378 on 2022/10/28.
//
#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int square[9][9] = {0};
    int last_row = 0;
    int last_col = (n - 1) / 2;
    square[0][(n - 1) / 2] = 1;
    for (int i = 2; i <= n * n; i++) {
            int copy_1 = last_row;
            int copy_2 = last_col;
            if (last_row == 0) {
                last_row = n - 1;
            } else {
                last_row = last_row - 1;
            }
            if (last_col == n - 1) {
                last_col = 0;
            } else {
                last_col = last_col + 1;
            }

            if(square[last_row][last_col] == 0){
                square[last_row][last_col] = i;
            } else{
                square[copy_1 + 1][copy_2] = i;
                last_row = copy_1 + 1;
                last_col = copy_2;
            }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",square[i][j]);
        }
        printf("\n");
    }

    return 0;
}