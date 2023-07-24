//
// Created by 25378 on 2022/12/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char *name;
    struct node *next;
} Node;

Node *head[5000] = {0};
Node *tail[5000] = {0};
Node *add[5000] = {0};
int judge[5000] = {0};

int hash(char *s);
int main(void){
    char *str = (char *) malloc(60000 * sizeof(char));
    char *record = str;
    int m = 0;
    int q = 0;
    scanf("%d%d", &m, &q);
    for(int i = 0; i < m; i++){
        scanf("%s", str);
        int len = (int)strlen(str);
        int t = hash(str);
        if(judge[t] == 0){
            add[i] = (Node *) malloc(sizeof (Node));
            add[i]->name = str;
            add[i]->next = NULL;
            head[t] = add[i];
            tail[t] = add[i];
            judge[t] = 1;
        } else {
            add[i] = (Node *) malloc(sizeof (Node));
            add[i]->name = str;
            add[i]->next = NULL;
            tail[t]->next = add[i];
            tail[t] = add[i];
        }
        str += len + 1;
    }

    char *query = (char*)malloc(1000 * sizeof(char));
    for(int i = 0; i < q; i++){
        scanf("%s", query);
        int k = hash(query);
        if(judge[k] == 0){
            printf("No\n");
        } else {
            int isFound = 0;
            Node *p = head[k];
            while(p != NULL){
                if(strcmp(p->name, query) == 0){
                    isFound = 1;
                    printf("Yes\n");
                    break;
                }
                p = p->next;
            }
            if(!isFound){
                printf("No\n");
            }
        }
    }

    for(int i = 0; i < m; i++){
        free(add[i]);
    }
    free(query);
    free(record);

    return 0;
}

int hash(char *s){
    int len = (int)strlen(s);
    int ret = 0;
    for(int i = 0; i < len; i++){
        ret = (ret + s[i] * (i + 1)) % 500000;
    }
    return ret;
}