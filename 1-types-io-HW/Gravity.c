//
// Created by 25378 on 2022/10/1.
//
#include <stdio.h>

int main()
{
    const double G = 6.674e-11, M = 77.15;
    double m, R;

    scanf("%lf %lf",&m,&R);

    printf("%.3e",G*M*m/(R*R));

    return 0;
}