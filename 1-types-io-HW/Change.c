//
// Created by 25378 on 2022/10/1.
//
#include <stdio.h>

int main()
{
    int n, a, b, c, d, e;

    scanf("%d", &n);

    a = n / 50;

    b = (n - a * 50) / 20;

    c = (n - a * 50 - b * 20) / 10;

    d = (n - a * 50 - b * 20 - c * 10) / 5;

    e = n - a * 50 - b * 20 - c * 10 - d * 5;

    printf("%d\n%d\n%d\n%d\n%d", a, b, c, d, e);

    return 0;
}