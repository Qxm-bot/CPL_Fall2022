//
// Created by 25378 on 2022/11/25.
//
#include <stdio.h>
#include <string.h>

int main(void) {
    char num[1000000] = {0};
    scanf("%s", num);
    int len = (int) strlen(num);
    int k = num[0] - '0';
    for (int i = 1; i < len; i++) {
        k = k % 9 + num[i] - '0';
    }
    printf("%d", k % 9);
    return 0;
}