//
// Created by 25378 on 2022/12/28.
//
#include <stdio.h>

int judge(int a[], int low, int high, int num);
int main(void){
    int a[1000] = {0};
    int query[1000] = {0};
    int n = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < q; i++){
        scanf("%d", &query[i]);
    }

    for(int i = 0; i < q; i++){
        printf("%d\n", judge(a, 0, n - 1, query[i]));
    }

    return 0;
}

int judge(int a[], int low, int high, int num){
    int mid = (low + high) / 2;
    if(low == high){
        if(a[low] == num){
            return low;
        } else{
            return -1;
        }
    } else if(low < high){
        if(a[mid] == num){
            return mid;
        } else if(a[mid] > num){
            return judge(a, low, mid - 1, num);
        } else{
            return judge(a, mid + 1, high, num);
        }
    } else {
        return -1;
    }
}