//
// Created by 25378 on 2022/11/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *S = (char*) malloc(100005 * sizeof(char));
    char *T = (char*) malloc(100005 * sizeof(char));
    int mark = 1;
    scanf("%s%s", S, T);
    int len_S = (int) strlen(S);
    int len_T = (int) strlen(T);
    for (int i = 0; i < len_S; i++) {
        if (*(S + i) == *T) {
            for (int j = 1; j < len_T; j++) {
                if (*(S + i + j) != *(T + j) || i + j >= len_S) {
                    mark = 0;
                    break;
                }
            }
            if (mark == 1) {
                printf("%d ", i);
            }
            mark = 1;
        }
    }
    free(S);
    free(T);
    return 0;
}