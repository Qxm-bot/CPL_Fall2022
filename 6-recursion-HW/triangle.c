//
// Created by 25378 on 2022/11/5.
//
#include <stdio.h>
#include <math.h>

char canvas[1024][2048] = {0};

void paint(int n, int x, int y);

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 2048; j++) {
            canvas[i][j] = ' ';
        }
    }
    paint(n, 0, (int) pow(2.0, n) - 1);
    for (int i = 0; i < (int) pow(2.0, n); i++) {
        for (int j = 0; j < (int) pow(2.0, n + 1); j++) {
            printf("%c", canvas[i][j]);
        }
        if (i != (int) pow(2.0, n) - 1) {
            printf("\n");
        }
    }
    return 0;
}

void paint(int n, int x, int y) {
    if (n == 1) {
        canvas[x][y] = '/';
        canvas[x][y + 1] = '\\';
        canvas[x + 1][y - 1] = '/';
        canvas[x + 1][y] = '_';
        canvas[x + 1][y + 1] = '_';
        canvas[x + 1][y + 2] = '\\';
    } else {
        paint(n - 1, x, y);
        paint(n - 1, x + (int) pow(2.0, n - 1), y - (int) pow(2.0, n - 1));
        paint(n - 1, x + (int) pow(2.0, n - 1), y + (int) pow(2.0, n - 1));
    }
}



