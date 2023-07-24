//
// Created by 25378 on 2022/10/28.
//
#include <stdio.h>
#include <math.h>
int Judge(int p, int q, int r, int k);
int SearchTheMax(int n);
int max(int a,int b, int c);

int main(void){
    int p = 0;
    int q = 0;
    int r = 0;
    scanf("%d %d %d",&p,&q,&r);
    int Max = max(SearchTheMax(p), SearchTheMax(q), SearchTheMax(r));
    int mark = 0;
    for(int i = Max + 1; i <= 40; i++){
        if(Judge(p,q,r,i)){
            mark = 1;
            printf("%d",i);
            break;
        }
    }
    if(mark == 0){
        printf("0");
    }
    return 0;
}

int Change(int a, int k){
    int digit = 0;
    int change_to_ten = 0;
    int copy = a;
    do{
        digit += 1;
        a /= 10;
    }while (a != 0);

    while(copy != 0){
        change_to_ten = change_to_ten + (int)pow(k * 1.0, digit - 1) * (copy / (int) pow(10.0, digit - 1));
        copy = copy - (int) pow(10.0, digit - 1) * (copy / (int) pow(10.0, digit - 1));
        digit--;
    }
    return change_to_ten;
}

int Judge(int p, int q, int r, int k){
    if(Change(p,k) * Change(q,k) == Change(r,k)){
        return 1;
    }
    return 0;
}

int SearchTheMax(int n) {
    if (n <= 9) {
        return n;
    } else if (n / 10 >= n % 10){
        return n / 10;
    } else{
        return n % 10;
    }
}

int max(int a, int b,int c){
    int max = a;
    if(b > max){
        max = b;
    }
    if(c > max){
        max = c;
    }
    return max;
}