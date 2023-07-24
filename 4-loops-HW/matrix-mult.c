//
// Created by 25378 on 2022/10/22.
//
#include <stdio.h>

int main(void) {
    int m, n, p;

    scanf("%d %d %d", &m, &n, &p);

    int a[100][100] = {0};
    int b[100][100] = {0};
    int c[100][100] = {0};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    int sum = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= p; j++) {
            for (int k = 1; k <= n; k++) {
                sum = sum + (a[i - 1][k - 1]) * (b[k - 1][j - 1]);
            }
            c[i - 1][j - 1] = sum;
            sum = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}