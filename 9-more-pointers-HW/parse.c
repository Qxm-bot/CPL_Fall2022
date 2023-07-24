//
// Created by 25378 on 2022/11/26.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char record_parameter = '\0';
    int judge = 0;
    int len_of_record = 0;
    char *s1 = (char *) malloc(128 * sizeof (char));
    scanf("%s", s1);
    int len = (int) strlen(s1);
    char *record = (char*) malloc(1024 * sizeof (char));
    *record = '\0';
    int *judge_char = (int *)malloc(('z' + 1) * sizeof (int));
    for(int i = 0; i <= 'z'; i++){
        *(judge_char + i) = 0;
    }
    for(int i = 0; i < len - 1; i++){
        if(*(s1 + i) != ':' && *(s1 + i + 1) != ':'){
            *(judge_char + *(s1 + i)) = 1;
        } else if(*(s1 + i) != ':' && *(s1 + i + 1) == ':'){
            *(judge_char + *(s1 + i)) = -1;
        }
    }
    if(*(s1 + len - 1) != ':'){
        *(judge_char + *(s1 + len - 1)) = 1;
    }
    char *string = (char*) malloc(1024 * sizeof (char));
    char *s = (char *) malloc(1024 * sizeof (char));
    scanf("%s", string);
    int len_of_string = (int)strlen(string);
    len_of_record += len_of_string;
    record = strcat(record, string);
    *(record + len_of_record) = '\n';
    *(record + len_of_record + 1) = '\0';
    len_of_record++;
    while(scanf("%s", s) != EOF){
        int len_of_s = (int)strlen(s);
        if(len_of_s == 2 && *s == '-' && *(judge_char + *(s + 1)) == 1){
            *(record + len_of_record) = *(s + 1);
            *(record + len_of_record + 1) = '\n';
            *(record + len_of_record + 2) = '\0';
            len_of_record += 2;
        } else if(len_of_s == 2 && *s == '-' && *(judge_char + *(s + 1)) == -1){
            record_parameter = *(s + 1);
            *(record + len_of_record) = *(s + 1);
            len_of_record++;
            *(record + len_of_record) = '=';
            len_of_record++;
            *(record + len_of_record + 1) = '\0';
            if(scanf("%s", s) != EOF) {
                len_of_s = (int) strlen(s);
                len_of_record += len_of_s;
                record = strcat(record, s);
                len_of_record++;
                *(record + len_of_record - 1) = '\n';
                *(record + len_of_record) = '\0';
            } else{
                judge = 1;
                break;
            }
        } else if (len_of_s == 2 && *s == '-' && *(judge_char + *(s + 1)) == 0){
            judge = 2;
            record_parameter = *(s + 1);
            break;
        }
    }

    if(judge == 0) {
        printf("%s", record);
    } else if (judge == 1){
        printf("%s: option requires an argument -- '%c'",string , record_parameter);
    } else {
        printf("%s: invalid option -- '%c'",string , record_parameter);
    }
    free(s1);
    free(s);
    free(string);
    free(record);
    free(judge_char);
    return 0;
}
