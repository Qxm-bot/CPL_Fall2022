//
// Created by 25378 on 2022/10/15.
//
#include <stdio.h>
#include <math.h>

int main(void)
{
    int len, N;

    scanf("%d %d", &len, &N);

    getchar();

    char str[30];

    for(int i = 0; i < len; i++){
        scanf("%c",&str[i]);
    }

    int sum = 0;
    int mark;

    if(N <= 10) {
         for (int i = 0; i < len; i++) {
             if((int) str[i] > N + 47){
                 mark = 0;
                 break;
             } else{
                sum = sum + ((int)str[i] - 48) * (int)pow(N * 1.0, len - i - 1.0);
                mark = 1;
            }
        }
         if(mark){
        printf("%d",sum);
         } else{
             printf("Error");
         }
    }

    if(N > 10){
        for(int i = 0; i < len; i++){
            if((int)str[i] > N + 54){
                mark = 0;
                break;
            } else{
                    if((int)str[i] > 64){
                        sum = sum + ((int)str[i] - 55) * (int)pow(N * 1.0, len - i -1.0);
                    } else{
                        sum = sum + ((int)str[i] - 48) * (int)pow(N * 1.0, len - i -1.0);
                    }
                    mark = 1;
                }
            }
        if(mark){
            printf("%d",sum);
        } else{
            printf("Error");
        }
    }

    return 0;
}