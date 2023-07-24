//
// Created by 25378 on 2022/11/11.
//
#include <stdio.h>

void paint(int a, int b, int c, int k, int T);

int main(void) {
    int T = 0;
    scanf("%d", &T);
    int data[50][3] = {0};
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &data[i][j]);
        }
    }
    for(int i = 0; i < T; i++){
        paint(data[i][0], data[i][1], data[i][2], i, T);
    }

    return 0;
}

void paint(int a, int b, int c, int k, int T) {
    char cuboid[82][82] = {0};

    for (int i = 1; i <= 2 * b + 2 * c + 1; i++) {
        for (int j = 1; j <= 2 * a + 2 * b + 1; j++) {
            cuboid[i][j] = ' ';
        }
    }

    if (b < c) {
        for (int i = 2 * b + 1; i <= 2 * c + 1; i += 2) {
            for (int j = 1; j <= 2 * a + 2 * b + 1; j += 2) {
                cuboid[i][j] = '+';
            }
            for (int j = 2; j <= 2 * a; j += 2) {
                cuboid[i][j] = '-';
            }
        }
        for (int i = 2 * b + 2; i <= 2 * c; i += 2) {
            for (int j = 1; j <= 2 * a + 2 * b + 1; j += 2) {
                cuboid[i][j] = '|';
            }
            for (int j = 2 * a + 2; j <= 2 * a + 2 * b; j += 2) {
                cuboid[i][j] = '/';
            }
        }
    }
    if(b == c){
        for (int j = 1; j <= 2 * a + 2 * b + 1; j += 2) {
            cuboid[2 * b + 1][j] = '+';
        }
        for (int j = 2; j <= 2 * a; j += 2) {
            cuboid[2 * b + 1][j] = '-';
        }
    }
    if(b > c){
        for(int i = 2 * c + 1; i <= 2 * b + 1; i += 2){
            for(int j = 2 * b + 2 - i; j <= 2 * b + 2 - i + 2 * a + 2 * c; j += 2){
                cuboid[i][j] = '+';
            }
            for(int j = 2 * b + 3 - i; j <= 2 * b + 2 * a - i + 1; j += 2){
                cuboid[i][j] = '-';
            }
        }
        for(int i = 2 * c + 2; i <= 2 * b; i += 2){
            for(int j = 2 * b + 2 - i; j <= 2 * b + 2 - i + 2 * a + 2 * c; j += 2){
                cuboid[i][j] = '/';
            }
            for(int j = 2 * a + 2 * b - i + 3; j <= 2 * b + 1 - i + 2 * a + 2 * c; j += 2){
                cuboid[i][j] = '|';
            }
        }
    }

    for (int i = 1; i <= (b > c ? 2 * c - 1: 2 * b - 1); i += 2) {
        for (int j = 2 * b + 2 - i; j <= 2 * a + 2 * b + 1; j += 2) {
            cuboid[i][j] = '+';
        }
        for(int j = 2 * b + 3 - i; j <= 2 * b + 2 * a + 1 - i; j += 2){
            cuboid[i][j] = '-';
        }
    }
    for(int i = 2; i <= (b > c ? 2 * c : 2 * b); i += 2){
        for(int j = 2 * b + 2 - i; j <= 2 * a + 2 * b; j += 2){
            cuboid[i][j] = '/';
        }
        for(int j = 2 * a + 2 * b + 3 - i; j <= 2 * a + 2 * b + 1; j += 2){
            cuboid[i][j] = '|';
        }
    }
    for (int i = ( b > c ? 2 * b + 2 : 2 * c + 2); i <= 2 * c + 2 * b; i += 2) {
        for (int j = 1; j <= 2 * a + 2 * b + 2 * c + 1 - i; j += 2) {
            cuboid[i][j] = '|';
        }
        for (int j = 2 * a + 2; j <= 2 * a + 2 * b + 2 * c + 2 - i; j += 2) {
            cuboid[i][j] = '/';
        }
    }

    for(int i = (b > c ? 2 * b + 3 : 2 * c + 3); i <= 2 * b + 2 * c + 1; i += 2){
        for(int j = 1; j <= 2 * a + 2 * b + 2 * c + 2 - i; j += 2){
            cuboid[i][j] = '+';
        }
        for(int j = 2; j <= 2 * a; j += 2){
            cuboid[i][j] = '-';
        }
    }

    for(int i = 1; i <= 2 * b + 2 * c + 1; i++){
        for(int j = 1; j <= 2 * a + 2 * b + 1; j++){
            printf("%c", cuboid[i][j]);
        }
        if(i != 2 * b + 2 * c + 1 || k != T - 1) {
            printf("\n");
        }
    }
}
/*
 *      +-+-+-+-+-+-+
 *     / / / / / / /|
      +-+-+-+-+-+-+ +
     / / / / / / /|/|
    +-+-+-+-+-+-+ + +
   / / / / / / /|/|/
  +-+-+-+-+-+-+ + +
 / / / / / / /|/|/
+-+-+-+-+-+-+ + +
| | | | | | |/|/
+-+-+-+-+-+-+ +
| | | | | | |/
+-+-+-+-+-+-+
 */