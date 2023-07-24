//Created on 2022/11/18
#include <stdio.h>

int main(void){
    int X;
    scanf("%x", &X);
    printf("%d\n%u\n%.6f\n%.3e", *(int*)&X, *(unsigned int*)&X,
           *(float*)&X, *(float*)&X);
    return 0;
}