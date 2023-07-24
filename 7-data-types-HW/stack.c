//
// Created by 25378 on 2022/11/14.
//
#include <stdio.h>

char stack[10000] = {0};
int len = 0;

void pop(void);

void top(int row, int n);

void print(int row, int n);

void push(char m);

int main(void) {
    int n;
    scanf("%d", &n);
    getchar();
    char put_in[10000][7] = {0};
    for (int i = 0; i < n; i++) {
        int len2 = 0;
        scanf("%c", &put_in[i][len2]);
        while (put_in[i][len2] != '\r' && put_in[i][len2] != '\n') {
            scanf("%c", &put_in[i][++len2]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (put_in[i][1] == 'u') {
            push(put_in[i][5]);
        } else if (put_in[i][0] == 'p' && put_in[i][1] == 'o') {
            pop();
        } else if (put_in[i][1] == 'o') {
            top(i, n);
        } else if (put_in[i][1] == 'r') {
            print(i, n);
        }
    }
    return 0;
}

void pop(void) {
    if (len == 0) {
        printf("Empty\n");
    } else {
        len--;
    }
}

void top(int row, int n) {
    if (len == 0) {
        printf("Empty\n");
    } else {
        printf("%c", stack[len - 1]);
        if(row != n - 1){
            printf("\n");
        }
    }
}

void print(int row, int n) {
    if (len == 0) {
        printf("Empty\n");
    } else {
        for (int i = len - 1; i >= 0; i--) {
            printf("| %c |\n", stack[i]);
        }
        printf("|===|");
        if(row != n - 1){
            printf("\n");
        }
    }
}

void push(char m) {
    len++;
    stack[len - 1] = m;
}