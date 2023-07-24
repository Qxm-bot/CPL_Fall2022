//
// Created by 25378 on 2022/11/4.
//
#include <stdio.h>
#include <math.h>

double Simpson(double a, double b, int t[], int n, int p);
double f(double x, int a[], int n, int p);
double F(double x, int a[], int n);
double integration(double l, double r, int a[], int n, int p, double m);
int main(void){
    int n = 0;
    int p = 0;
    int a[21] = {0};
    scanf("%d%d", &n, &p);
    for(int i = 0; i <= n; i++){
        scanf("%d", &a[i]);
    }
    double l = 0;
    double r = 0;
    scanf("%lf%lf", &l, &r);
    if(p == 1){
        printf("%f", F(r, a, n) - F(l, a, n));
    } else{
        printf("%f", integration(l, r, a, n, p, pow(10.0, -4)));
    }
    return 0;
}

double Simpson(double a, double b, int t[], int n, int p){
    return (4 * f((a + b) / 2, t, n, p) + f(a, t, n, p) + f(b, t, n, p)) * (b - a) / 6;
}

double f(double x, int a[], int n, int p){
    double sum = 0;
    for(int i = 0; i <= n; i++){
        sum = sum + a[i] * pow(x, i);
    }
    return pow(sum, p);
}

double F(double x, int a[], int n){
    double sum = 0;
    for(int i = 0; i <= n; i++){
        sum = sum + a[i] * pow(x, i + 1) / (i + 1);
    }
    return sum;
}

double integration(double l, double r, int a[], int n, int p, double m){
    double mid = (l + r) / 2;
    double S = Simpson(l, r, a, n, p);
    double SL = Simpson(l, mid, a, n, p);
    double SR = Simpson(mid, r, a, n, p);
    if(fabs(SL + SR - S) <= 15 * m){
        return SL + SR +(SL + SR - S) / 15;
    } else{
        return integration(l, mid, a, n, p, m / 2) + integration(mid, r, a, n, p, m / 2);
    }
}