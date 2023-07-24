//
// Created by 25378 on 2022/11/25.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mystrcat(char *s1, char *s2);

int main(void) {
    char *s1 = (char*)malloc(2001 * sizeof (char));
    char *s2 = (char*)malloc(1001 * sizeof (char));
    int T = 0;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%s%s", s1, s2);
        mystrcat(s1, s2);
    }
    free(s1);
    free(s2);
    return 0;
}

void mystrcat(char *s1, char *s2) {
    int len1 = (int) strlen(s1);
    int len2 = (int) strlen(s2);
    int mark = 1;
    int mark2 = 0;
    int record = 0;
    for (int i = 0; i < len1; i++) {
        if (*(s1 + i) == *s2) {
            for (int j = i; j < len1; j++) {
                if ( j - i >= len2 || *(s1 + j) != *(s2 + j - i) ) {
                    mark = 0;
                    break;
                }
            }
            if (mark == 1) {
                mark2 = 1;
                record = len1 - i;
                break;
            }
        }
        mark = 1;
    }

    if (mark2) {
        for (int i = 0; i < len2 - record + 1; i++) {
            *(s1 + len1 + i)  = *(s2 + record + i);
        }
    } else {
        for(int i = 0; i < len2 + 1; i++){
            *(s1 + len1 + i) = *(s2 + i);
        }
    }
    printf("%s\n", s1);
}