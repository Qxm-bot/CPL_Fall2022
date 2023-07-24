//
// Created by 25378 on 2022/10/2.
//
#include <stdio.h>
#include <math.h>

int main()
{
    int p,q;

    scanf("%d %d",&p,&q);

    double a = pow(fabs(q/(-2.0) + sqrt(q/2.0*q/2 + p/3.0*p/3*p/3)),1.0/3),
            b = pow(fabs(q/(-2.0) - sqrt(q/2.0*q/2 + p/3.0*p/3*p/3)),1.0/3);

    if((q/(-2.0) + sqrt(q/2.0*q/2 + p/3.0*p/3*p/3))<0){
        a = -a;
    }
    if((q/(-2.0) - sqrt(q/2.0*q/2 + p/3.0*p/3*p/3))<0){
        b = -b;
    }

    double X1 = a + b;

    printf("%.3f",X1);

    return 0;
}