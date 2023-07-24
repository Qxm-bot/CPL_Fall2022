//
// Created by 25378 on 2022/10/22.
//
#include <stdio.h>

int main(void) {
    int n = 0;
    int m = 0;
    int x0 = 0;
    int y0 = 0;
    int ans = 0;
    char map[52][52] = {'\0'};

    for (int i = 0; i < 52; i++) {
        for (int j = 0; j < 52; j++) {
            map[i][j] = '_';
        }
    }

    scanf("%d %d %d %d", &n, &m, &x0, &y0);
    getchar();
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            scanf("%c", &map[i][j]);
            if (map[i][j] == '#') {
                ans++;
            }
        }
        getchar();
    }

    printf("%d\n", ans);

    int x = x0;
    int y = y0;
    int count = 0;
    while (count <= ans - 1) {
        printf("%d %d\n", x, y);
        map[x][y] = '_';
        int check[4][2] = {{0,  1},
                           {0,  -1},
                           {1,  0},
                           {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int new_x = x + check[i][0];
            int new_y = y + check[i][1];
            if (map[new_x][new_y] == '#') {
                x = new_x;
                y = new_y;
                break;
            }
        }
        count++;
    }

    return 0;
}
