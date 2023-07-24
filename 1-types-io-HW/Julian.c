//
// Created by 25378 on 2022/10/2.
//
#include <stdio.h>

int main()
{
    int year,month,day;

    scanf("%d %d %d",&year,&month,&day);

    int a = (int)((14-month)/12),
        y = year + 4800 - a,
        m = month + 12*a -3,
        JDN = day + (int)((153*m + 2)/5) + 365*y + y/4 - y/100 + y/400 -32045;

    printf("%d",JDN);

    return 0;
}