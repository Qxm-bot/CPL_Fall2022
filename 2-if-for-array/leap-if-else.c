//
// Created by 25378 on 2022/10/7.
//
#include <stdio.h>

int main() {
    int year;

    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        printf("The year is a leap year.");
    } else {
        printf("The year isn't a leap year.");
    }

    return 0;
}