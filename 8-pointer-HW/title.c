//
// Created by 25378 on 2022/11/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char *string = (char*) malloc(4096 * sizeof (char));
    gets(string);
    int len = (int) strlen(string);
    for(int i = 0; i < len; i++){
        if((int)*(string + i) >= 'A' && (int)*(string + i) <= 'Z'){
            if(i > 0 && *(string + i - 1) != ' '){
                *(string + i) = (char)((int)*(string + i) + 'a' - 'A');
            }
        } else if((int)*(string + i) >= 'a' && (int)*(string + i) <= 'z'){
            if(i == 0 || (i > 0 && *(string + i - 1) == ' ')){
                *(string + i) = (char)((int)*(string + i) + 'A' - 'a');
            }
        }
    }
    printf("%s", string);
    free(string);
    return 0;
}