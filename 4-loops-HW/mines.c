//
// Created by 25378 on 2022/10/22.
//
#include <stdio.h>

int main(void) {
    int n;

    char board[100][100] = {'\0'};

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%c", &board[i][j]);
        }
        getchar();
    }

    char new_board[102][102] = {'\0'};

    for (int i = 0; i < 102; i++) {
        for (int j = 0; j < 102; j++) {
            new_board[i][j] = 'o';
        }
    }
    int line = 0;
    int col = 0;

    for (line = 1; line < n + 1; line++) {
        for (col = 1; col < n + 1; col++) {
            new_board[line][col] = board[line - 1][col - 1];
        }
    }

    for (line = 1; line < n + 1; line++) {
        for (col = 1; col < n + 1; col++) {
            if (new_board[line][col] == 'o') {
                int vectors[8][2] = {{0,  1},
                                     {0,  -1},
                                     {1,  0},
                                     {1,  -1},
                                     {1,  1},
                                     {-1, 0},
                                     {-1, -1},
                                     {-1, 1}};
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    int newline = line + vectors[k][0];
                    int newcol = col + vectors[k][1];
                    if (new_board[newline][newcol] == '*') {
                        count++;
                    }
                }
                new_board[line][col] = (char) ((int) '1' + count - 1);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            printf("%c", new_board[i][j]);
        }
        if (i != n) {
            printf("\n");
        }
    }

    return 0;
}