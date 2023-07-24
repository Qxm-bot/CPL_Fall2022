//
// Created by 25378 on 2022/10/8.
//
#include <stdio.h>

int main()
{
    int n;

    scanf("%d",&n);

    int m = 1, sum = 0;

    for (int i = 1; i < n+1; i++) {
        m = m * (i % 10007);
        sum = sum + (m % 10007);
        m = m % 10007;
        sum = sum % 10007;
    }

    printf("%d",sum);

    return 0;
}