//
// Created by 25378 on 2022/10/8.
//
#include <stdio.h>
#include <math.h>

int main()
{
    int n,k;

    char a[(int)pow(10.0, 4.0)];

    char b[(int)pow(10.0, 4.0)];

    scanf("%d",&n);

    getchar();

    for (int q = 0; q < n; q++){
        scanf("%c",&a[q]);
    }

    scanf("%d",&k);

    for (int i = 0; i < k; i++) {
        b[i] = a[k-1-i];
    }

    for (int p = k; p < n; p++) {
        b[p] = a[k+n-1-p];
    }

    for (int t = 0; t < n; t++) {
        printf("%c", b[t]);
    }

    return 0;
}