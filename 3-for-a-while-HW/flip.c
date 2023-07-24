//
// Created by 25378 on 2022/10/14.
//
#include <stdio.h>

int main(void)
{
    int n;

    scanf("%d",&n);

    int bit[2000]={0};

    for(int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if(j % i == 0){
                if(bit[j-1] == 0){
                    bit[j-1] = 1;
                } else{
                    bit[j-1] =0;
                }
            }
        }
    }

    for(int k = 0; k < n; k++){
        if(bit[k] == 1){
            printf("%d ",k + 1);
        }
    }

    return 0;
}