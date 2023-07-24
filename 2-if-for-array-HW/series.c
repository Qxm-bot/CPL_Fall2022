//
// Created by 25378 on 2022/10/8.
//
#include <stdio.h>
#include <math.h>

int main()
{
    double x;
    int n;

    scanf("%lf %d",&x,&n);

    double total = 0.0;

    for (int i = 0; i < n + 1; i++){
        total = total + pow(-1.0, 1.0*i)*pow(x,2.0*i + 1)/(2*i + 1);
    }

    printf("%.10f",4*total);

    return 0;
}