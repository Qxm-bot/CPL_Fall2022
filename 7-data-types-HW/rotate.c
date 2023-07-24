//
// Created by 25378 on 2022/11/13.
//
#include <stdio.h>
#include <string.h>

void rotate(int x1, int x2, int y1, int y2, int count, char roll[], int len, int a, int b, int c);

int main(void) {
    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d%d%d", &a, &b, &c);

    char roll[1000] = {0};

    scanf("%s", roll);
    int len = (int)strlen(roll);
    rotate(0, a, 0, b, 0, roll, len, a, b, c);

    return 0;
}

void rotate(int x1, int x2, int y1, int y2, int count, char roll[], int len, int a, int b, int c) {
    if (count == len) {
        printf("%d %d %d %d", x1, x2, y1, y2);
    } else if ((x2 - x1 == a && y2 - y1 == b) || (x2 - x1 == b && y2 - y1 == a)) {
        if (roll[count] == 'W') {
            rotate(x1 - c, x1, y1, y2, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'S') {
            rotate(x2, x2 + c, y1, y2, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'A') {
            rotate(x1, x2, y1 - c, y1, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'D') {
            rotate(x1, x2, y2, y2 + c, count + 1, roll, len, a, b, c);
        }
    } else if ((x2 - x1 == a && y2 - y1 == c) || (x2 - x1 == c && y2 - y1 == a)) {
        if (roll[count] == 'W') {
            rotate(x1 - b, x1, y1, y2, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'S') {
            rotate(x2, x2 + b, y1, y2, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'A') {
            rotate(x1, x2, y1 - b, y1, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'D') {
            rotate(x1, x2, y2, y2 + b, count + 1, roll, len, a, b, c);
        }
    } else if ((x2 - x1 == b && y2 - y1 == c) || (x2 - x1 == c && y2 - y1 == b)) {
        if (roll[count] == 'W') {
            rotate(x1 - a, x1, y1, y2, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'S') {
            rotate(x2, x2 + a, y1, y2, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'A') {
            rotate(x1, x2, y1 - a, y1, count + 1, roll, len, a, b, c);
        } else if (roll[count] == 'D') {
            rotate(x1, x2, y2, y2 + a, count + 1, roll, len, a, b, c);
        }
    }
}