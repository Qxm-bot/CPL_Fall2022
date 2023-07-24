//
// Created by 25378 on 2022/10/7.
//
#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    int a[(int)(2*pow(10.0,5.0)-1)];
    int b[(int)pow(10.0,6.0)];

    scanf("%d",&n);

    for (int p = 0; p < 2*n -1; p++){
        b[p] = 0;
    }

    for (int i=0; i < 2*n - 1;i++){
        scanf("%d",&a[i]);
    }

    for (int k = 0; k < 2*n -1; k++){
        b[a[k]]++;
    }

    for ( int q = 0; q < 2*n - 1; q++){
        if (b[a[q]]==1){
            printf("%d",a[q]);
        }
    }

    return 0;
}