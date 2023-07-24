//
// Created by 25378 on 2022/10/7.
//
#include <stdio.h>

int main()
{
    int num,i;

    scanf("%d",&i);

    int max = i;

    for (num = 0; i != 1; num++) {
        if (i % 2 != 0) {
            i = 3 * i + 1;
        } else {
            i = i / 2;
        }
        if (i >= max){
            max = i;
        }
    }

    printf("%d %d", num, max);

    return 0;
}