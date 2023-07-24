//
// Created by 25378 on 2022/10/7.
//
#include <stdio.h>

int main ()
{
    int NUM,i;

    printf("Please input NUM:");

    scanf ("%d",&NUM);

    int a[NUM] ;

    for ( i = 0; i < NUM; i++){
        printf("Please input a[%d]:",i);
        scanf("%d",&a[i]);
    }

    int min = a[0];

    for ( int i = 1; i<NUM ; i++ ){
        if ( a[i] < min){
            min = a[i];
        }
    }

    printf("%d",min);
    return 0;
}