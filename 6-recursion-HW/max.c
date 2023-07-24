//
// Created by 25378 on 2022/11/4.
//
#include <stdio.h>

#define N 100001
int ans[N][2] = {0};

void maximum_interval(int a[], int len, int l, int r);

int main(void) {
    int n = 0;
    scanf("%d", &n);
    int sequence[N] = {0};
    for (int i = 1; i <= n; i++) {
        scanf("%d", &sequence[i]);
    }
    maximum_interval(sequence, n, 1, n);
    for(int i = 1; i <= n; i++){
        printf("%d %d", ans[i][0], ans[i][1]);
        if(i != n) {
            printf("\n");
        }
    }

    return 0;
}

void maximum_interval(int a[], int len, int l, int r) {
    int max = a[l];
    int mark = l;
    for (int i = l; i <= r; i++) {
        if (a[i] > max) {
            max = a[i];
            mark = i;
        }
    }
    ans[mark][0] = l;
    ans[mark][1] = r;
    if(l != r) {
        if (mark == l) {
            maximum_interval(a, len - 1, l + 1, r);
        }else if(mark == r){
            maximum_interval(a, len - 1, l, r - 1);
        } else{
            maximum_interval(a, mark - l, l, mark - 1);
            maximum_interval(a, r - mark, mark + 1, r);
        }
    }
}