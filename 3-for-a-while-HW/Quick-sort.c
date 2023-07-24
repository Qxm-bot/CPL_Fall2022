//
// Created by 25378 on 2022/10/15.
//
#include <stdio.h>

int main(void)
{
    int n,k;
    scanf("%d %d",&n,&k);

    int a[10001] = {0};
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    int l = 1;
    int r = n;
    int t;
    int mid = a[k];
    while(l != r){
        while(l != r && a[l] < mid){
            l = l + 1;
        }while(r != l && a[r] >= mid){
            r = r - 1;
        }
        t = a[l];
        a[l] = a[r];
        a[r] = t;
    }

    int find;
    for(find = 1; find <= n; find++){
        if(a[find] == mid){
            break;
        }
    }

    if(l < find){
        t = a[l];
        a[l] = a[find];
        a[find] = t;
    }

    for(int i = 1; i <= n; i++){
        printf("%d ",a[i]);
    }

    return 0;
}