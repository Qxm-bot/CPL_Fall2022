//
// Created by 25378 on 2022/10/9.
//
#include <stdio.h>

int min(int m, int n);

int max(int c, int d);

int main() {
    char b[25];
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int x3 = 0;
    int y3 = 0;
    int n = 0;
    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
    if ((y1 == y2) && (y2 == y3) && (min(x1, x2) < x3) && (x3 < max(x1, x2))) {
        b[0] = 'U';
        for (int i = 1; i < max(x1, x2) - min(x1, x2) + 1; i++) {
            b[i] = 'R';
        }
        b[max(x1, x2) - min(x1, x2) + 1] = 'D';
        if ((min(x1, x2)) != x1) {
            for (int k = 0; k < max(x1, x2) - min(x1, x2) + 2; k++) {
                if (b[k] == 'U') {
                    b[k] = 'D';
                } else if (b[k] == 'D') {
                    b[k] = 'U';
                } else if (b[k] == 'R') {
                    b[k] = 'L';
                }
            }
            n = max(x1, x2) - min(x1, x2) + 2;
            printf("%d\n", n);
            for (int i = n - 1; i >= 0; i--) {
                printf("%c", b[i]);
            }
        } else {
            n = max(x1, x2) - min(x1, x2) + 2;
            printf("%d\n", n);
            for (int t = 0; t < n; t++) {
                printf("%c", b[t]);
            }
        }
    } else if ((x1 == x2) && (x2 == x3) && (min(y1, y2) < y3) && (y3 < max(y1, y2))) {
        b[0] = 'R';
        for (int i = 1; i < max(y1, y2) - min(y1, y2) + 1; i++) {
            b[i] = 'D';
        }
        b[max(y1, y2) - min(y1, y2) + 1] = 'L';
        if ((max(y1, y2)) != y1) {
            for (int k = 0; k < max(y1, y2) - min(y1, y2) + 2; k++) {
                if (b[k] == 'D') {
                    b[k] = 'U';
                } else if (b[k] == 'L') {
                    b[k] = 'R';
                } else if (b[k] == 'R') {
                    b[k] = 'L';
                }
            }
            n = max(y1, y2) - min(y1, y2) + 2;
            printf("%d\n", n);
            for (int i = n - 1; i >= 0; i--) {
                printf("%c", b[i]);
            }
        } else {
            n = max(y1, y2) - min(y1, y2) + 2;
            printf("%d\n", n);
            for (int i = 0; i < n; i++) {
                printf("%c", b[i]);
            }
        }
    } else if (x1 == x2 && y1 > y2) {
        for (int i = 0; i < y1 - y2; i++) {
            b[i] = 'D';
        }
        n = y1 - y2;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (x1 == x2 && y1 < y2) {
        for (int i = 0; i < y2 - y1; i++) {
            b[i] = 'U';
        }
        n = y2 - y1;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (y1 == y2 && x1 > x2) {
        for (int i = 0; i < x1 - x2; i++) {
            b[i] = 'L';
        }
        n = x1 - x2;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (y1 == y2 && x1 < x2) {
        for (int i = 0; i < x2 - x1; i++) {
            b[i] = 'R';
        }
        n = x2 - x1;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (x1 < x2 && y1 < y2) {
        if ((x3 == x2 && y3 >= y1 && y3 < y2) || (y3 == y1 && x3 <= x2 && x3 > x1)) {
            for (int i = 0; i < y2 - y1; i++) {
                b[i] = 'U';
            }
            for (int i = y2 - y1; i < y2 - y1 + x2 - x1; i++) {
                b[i] = 'R';
            }
        } else {
            for (int i = 0; i < x2 - x1; i++) {
                b[i] = 'R';
            }
            for (int i = x2 - x1; i < x2 - x1 + y2 - y1; i++) {
                b[i] = 'U';
            }
        }
        n = x2 - x1 + y2 - y1;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (x1 < x2 && y1 > y2) {
        if ((x3 == x2 && y3 <= y1 && y3 > y2) || (y3 == y1 && x3 <= x2 && x3 > x1)) {
            for (int i = 0; i < y1 - y2; i++) {
                b[i] = 'D';
            }
            for (int i = y1 - y2; i < y1 - y2 + x2 - x1; i++) {
                b[i] = 'R';
            }
        } else {
            for (int i = 0; i < x2 - x1; i++) {
                b[i] = 'R';
            }
            for (int i = x2 - x1; i < x2 - x1 + y1 - y2; i++) {
                b[i] = 'D';
            }
        }
        n = x2 - x1 + y1 - y2;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (x1 > x2 && y1 < y2) {
        if ((x3 == x2 && y3 >= y1 && y3 < y2) || (y3 == y1 && x3 >= x2 && x3 < x1)) {
            for (int i = 0; i < y2 - y1; i++) {
                b[i] = 'U';
            }
            for (int i = y2 - y1; i < y2 - y1 + x1 - x2; i++) {
                b[i] = 'L';
            }
        } else {
            for (int i = 0; i < x1 - x2; i++) {
                b[i] = 'L';
            }
            for (int i = x1 - x2; i < x1 - x2 + y2 - y1; i++) {
                b[i] = 'U';
            }
        }
        n = x1 - x2 + y2 - y1;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    } else if (x1 > x2 && y1 > y2) {
        if (((x3 == x2) && (y3 <= y1) && (y3 > y2)) || ((y3 == y1) && (x3 >= x2) && (x3 < x1))) {
            for (int i = 0; i < y1 - y2; i++) {
                b[i] = 'D';
            }
            for (int i = y1 - y2; i < y1 - y2 + x1 - x2; i++) {
                b[i] = 'L';
            }
        } else {
            for (int i = 0; i < x1 - x2; i++) {
                b[i] = 'L';
            }
            for (int i = x1 - x2; i < x1 - x2 + y1 - y2; i++) {
                b[i] = 'D';
            }
        }
        n = x1 - x2 + y1 - y2;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", b[i]);
        }
    }
    return 0;
}

int min(int m, int n) {
    if (m < n) {
        return m;
    } else {
        return n;
    }
}

int max(int c, int d) {
    if (c < d) {
        return d;
    } else {
        return c;
    }
}