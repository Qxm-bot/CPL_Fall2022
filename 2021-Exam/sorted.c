//
// Created by 25378 on 2022/12/28.
//
#include <stdio.h>

int isInOrder(int sequence[], int len);
int main(void){
    int T = 0;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        int n = 0;
        int m = 0;
        scanf("%d%d", &n, &m);
        int sequence[1000] = {0};
        for(int j = 0; j < n; j++){
            scanf("%d", &sequence[j]);
        }
        int operate[1000] = {0};
        for(int j = 0; j < m; j++){
            scanf("%d", &operate[j]);
        }

        for(int j = 0; j < m; j++){
            int index = operate[j] - 1;
            if(index != 0){
                int record = sequence[index];
                for(int k = index; k > 0; k--){
                    sequence[k] = sequence[k - 1];
                }
                sequence[0] = record;
            }
        }

        if(isInOrder(sequence, n)){
            printf("I love C programming language\n");
        } else{
            printf("mayi is a good teacher\n");
        }
    }

    return 0;
}

int isInOrder(int sequence[], int len){
    if(len == 1){
        return 1;
    }
    for(int i = 0; i < len - 1; i++){
        if(sequence[i] > sequence[i + 1]){
            return 0;
        }
    }
    return 1;
}