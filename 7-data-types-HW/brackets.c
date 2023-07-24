//
// Created by 25378 on 2022/11/14.
//
#include <stdio.h>
#include <string.h>

int main(void){
    char bracket[100000] = {0};
    char stack[100000] = {0};
    int judge[100000] = {0};
    int T = 0;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        int len_of_stack = 0;
        scanf("%s", bracket);
        int len = (int) strlen(bracket);
        for(int j = 0; j < len; j++){
            if((bracket[j] == ')' && len_of_stack != 0 && stack[len_of_stack - 1] == '(')
            || (bracket[j] == '}' && len_of_stack != 0 && stack[len_of_stack - 1] == '{')
            || (bracket[j] == ']' && len_of_stack != 0 && stack[len_of_stack - 1] == '[')){
                len_of_stack--;
            } else{
                len_of_stack++;
                stack[len_of_stack - 1] = bracket[j];
            }
        }
        if(len_of_stack == 0){
            judge[i - 1] = 1;
        } else{
            judge[i - 1] = 0;
        }
    }
    for(int i = 0; i < T; i++){
        if(judge[i] == 1){
            printf("True");
        } else{
            printf("False");
        }
        if(i != T - 1){
            printf("\n");
        }
    }

    return 0;
}