//
// Created by 25378 on 2022/11/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process(char *s);
char *output = 0;
int len_of_output= 0;
int mark = 0;
int mark2 = 0;
int main(void){
    output = (char*) malloc(36855 * sizeof(char));
    *output = '\0';
    char *s = (char*)malloc(4096 * sizeof (char));
    while(scanf("%s", s) != EOF){
        char *position = strchr(s, ';');
        if(position == NULL){
            process(s);
        } else{
            *position = '\0';
            process(s);
            *(output + len_of_output) = '\n';
            *(output + len_of_output + 1) = '\0';
            len_of_output++;
            process(position + 1);
        }
    }

    if(mark2){
        printf("Compile Error");
    } else{
        printf("%s ", output);
    }
    free(s);
    free(output);

    return 0;
}

void process(char *s){
    int len = (int)strlen(s);
    if(len != 0) {
        if((strcmp(s ,"const") == 0)
           ||(strcmp(s ,"int") == 0)
           ||(strcmp(s ,"float") == 0)
           ||(strcmp(s ,"double") == 0)
           ||(strcmp(s ,"long") == 0)
           ||(strcmp(s ,"static") == 0)
           ||(strcmp(s ,"void") == 0)
           ||(strcmp(s ,"char") == 0)
           ||(strcmp(s ,"extern") == 0)
           ||(strcmp(s ,"return") == 0)
           ||(strcmp(s ,"break") == 0)
           ||(strcmp(s ,"enum") == 0)
           ||(strcmp(s ,"struct") == 0)
           ||(strcmp(s ,"typedef") == 0)
           ||(strcmp(s ,"union") == 0)
           ||(strcmp(s ,"goto") == 0)){
            output = strcat(output,"reserved ");
            len_of_output += 9;
            mark = 1;
        } if(mark == 0) {
            int judge = 1;
            for(int i = 0; i < len; i++){
                if(*(s + i) < '0' || *(s + i) > '9'){
                    judge = 0;
                    break;
                }
            }
            if (judge) {
                output = strcat(output,"integer ");
                len_of_output += 8;
                mark = 1;
            }
        } if (mark == 0) {
            int count = 0;
            int judge_number = 1;
            for(int i = 0; i < len; i++){
                if(*(s + i) == '.'){
                    count++;
                } else if(*(s + i) > '9' || *(s + i) < '0'){
                    judge_number = 0;
                    break;
                }
            }if(count == 1 && judge_number == 1) {
                output = strcat(output, "float ");
                mark = 1;
                len_of_output += 6;
            }
        } if (mark == 0) {
            if((strcmp(s, "+") == 0)
               || (strcmp(s, "-") == 0)
               || (strcmp(s, "*") == 0)
               || (strcmp(s, "/") == 0)
               || (strcmp(s, "=") == 0)
               || (strcmp(s, "==") == 0)
               || (strcmp(s, "!=") == 0)
               || (strcmp(s, ">=") == 0)
               || (strcmp(s, "<=") == 0)
               || (strcmp(s, ">") == 0)
               || (strcmp(s, "<") == 0)) {
                output = strcat(output, "operator ");
                len_of_output += 9;
                mark = 1;
            }
        } if (mark == 0) {
            int judge_first_char = 1;
            if(*s >= '0' && *s <= '9'){
                judge_first_char = 0;
            }
            if(judge_first_char){
                int t = 1;
                for(int i = 0; i < len; i++){
                    if(*(s + i) != '_' && (*(s + i) < '0' || *(s + i) > '9')
                       && (*(s + i) < 'a' || *(s + i) > 'z') && (*(s + i) < 'A' || *(s + i) > 'Z')){
                        t = 0;
                        break;
                    }
                }
                if(t){
                    output = strcat(output, "variable ");
                    mark = 1;
                    len_of_output += 9;
                }
            }
        }
        if(mark == 0){
            mark2 = 1;
        }
        mark = 0;
    }
}