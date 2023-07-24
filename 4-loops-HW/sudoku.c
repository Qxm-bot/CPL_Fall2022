//
// Created by 25378 on 2022/10/21.
//
#include <stdio.h>

int main(void) {
    int mark = 1;
    int board[9][9] = {0};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] > 9 || board[i][j] < 1) {
                mark = 0;
                break;
            }
        }
    }

    if (mark != 0) {
        int check[10] = {0};
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sum = sum + board[i][j];
                check[board[i][j]]++;
            }
            if (sum != 45) {
                mark = 0;
            }
            for (int k = 1; k < 10; k++) {
                if (check[k] != 1) {
                    mark = 0;
                    break;
                }
            }
            if (mark == 0) {
                break;
            }
            sum = 0;
            for (int p = 1; p < 10; p++) {
                check[p] = 0;
            }
        }

        sum = 0;
        int check_2[10] = {0};
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sum = sum + board[j][i];
                check_2[board[j][i]]++;
            }
            if (sum != 45) {
                mark = 0;
            }
            for (int k = 1; k < 10; k++) {
                if (check_2[k] != 1) {
                    mark = 0;
                    break;
                }
            }
            if (mark == 0) {
                break;
            }
            sum = 0;
            for (int p = 1; p < 10; p++) {
                check_2[p] = 0;
            }
        }

        sum = 0;
        int check_3[10] = {0};
        int a[3][3] = {0};
        for (int m = 0; m <= 6; m += 3) {
            for (int n = 0; n <= 6; n += 3) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        a[i][j] = board[i + m][j + n];
                        sum = sum + a[i][j];
                        check_3[a[i][j]]++;
                    }
                }
                if (sum != 45) {
                    mark = 0;
                }
                for (int i = 1; i < 10; i++) {
                    if (check_3[i] != 1) {
                        mark = 0;
                        break;
                    }
                }
                sum = 0;
                for (int p = 1; p < 10; p++) {
                    check_3[p] = 0;
                }
            }
        }
    }

    if (mark) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}