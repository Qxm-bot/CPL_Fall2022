//
// Created by 25378 on 2022/10/28.
//
#include <stdio.h>
#include <math.h>

int main(void){
    int IsPrime(int n);
    int Judge(int n);

    int n = 0;
    scanf("%d", &n);

    int sum = 0;
    for(int i = 2; i <= n ; i++){
        if (Judge(i)){
            sum++;
        }
    }

    printf("%d", sum);

    return 0;
}

int IsPrime(int n){
    if(n <= 1){
        return 0;
    }
    for(int i = 2; i <= sqrt(n + 0.5); i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}

int Judge(int n){
    int copy = n;
    int copy_2 = n;
    int inverse_n = 0;
    int digit = 0;
    do{
        digit += 1;
        n /= 10;
    } while( n != 0);

    int k = 0;
    while (copy != 0){
        inverse_n = inverse_n + (int)pow(10.0,k) * (copy / (int)pow(10.0,digit - 1));
        copy = copy % (int)pow(10.0, digit - 1);
        digit --;
        k++;
    }
    if(IsPrime(copy_2) && IsPrime(inverse_n)){
        return 1;
    }
    return 0;
}