//
// Created by 25378 on 2022/11/13.
//
#include <stdio.h>

int pour(int a, int b, int c, int count, int k, int a0, int b0, int c0, int Va, int Vb, int Vc);
int operate(int a, int b, int Va);

int main(void){
    int k = 0;
    int Va = 0;
    int Vb = 0;
    int Vc = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int a0 = 0;
    int b0 = 0;
    int c0 = 0;
    scanf("%d%d%d%d%d%d%d%d%d%d", &k, &Va, &Vb, &Vc, &a, &b, &c, &a0, &b0, &c0);
    if(pour(a, b, c, 0, k, a0, b0, c0, Va, Vb, Vc) != 0){
        printf("Yes");
    } else{
        printf("No");
    }
    return 0;
}

int pour(int a, int b, int c, int count, int k, int a0, int b0, int c0, int Va, int Vb, int Vc){
    if (count <= k && a == a0 && b == b0 && c == c0) {
        return 1;
    }
    if(count >= k){
        return 0;
    }
    return pour(0, operate(b, a, Vb), c, count + 1, k, a0, b0, c0, Va, Vb, Vc)
         + pour(operate(a, b, Va), 0, c, count + 1, k, a0, b0, c0, Va, Vb, Vc)
         + pour(0, b, operate(c, a, Vc), count + 1, k, a0, b0, c0, Va, Vb, Vc)
         + pour(operate(a, c, Va), b, 0, count + 1, k, a0, b0, c0, Va, Vb, Vc)
         + pour(a, 0, operate(c, b, Vc), count + 1, k, a0, b0, c0, Va, Vb, Vc)
         + pour(a, operate(b, c, Vb), 0, count + 1, k, a0, b0, c0, Va, Vb, Vc);
}

int operate(int a, int b, int Va){
    if(b + a > Va){
        a = Va;
    } else{
        a = b + a;
    }
    return a;
}