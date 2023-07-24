//
// Created by 25378 on 2023/2/25.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define B 2000
typedef struct node{
    char s[2000];
    struct node *next;
    int len;
} node;

node *head = NULL;
void adding(char *s, node **bf, node *nt);
int main(void){
    /*
    int n = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    char *s = (char *) malloc((n + 1) * sizeof (char));
    scanf("%s", s);
    for(int i = 0; i < q; i++){
        char *f = (char *) malloc(2 * sizeof (char));
        scanf("%s", f);
        if(f[0] == 'I'){
            int index = 0;
            scanf("%d", &index);
            char *t = (char *) malloc(100005 * sizeof (char));
            scanf("%s", t);
            int len = (int)strlen(t);
            char *s1 = (char *) malloc((n + len + 1) * sizeof (char));
            for(int j = 0; j < index; j++){
                s1[j] = s[j];
            }
            for(int j = index; j < index + len; j++){
                s1[j] = t[j - index];
            }
            for(int j = index + len; j < n + len; j++){
                s1[j] = s[j - len];
            }
            free(s);
            s = s1;
            n = n + len;
        } else if(f[0] == 'Q'){
            int index = 0;
            scanf("%d", &index);
            printf("%c\n", s[index - 1]);
        }
    }
     */
    int n = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    char *s = (char *) malloc(100001 * sizeof (char));
    scanf("%s", s);
    adding(s, &head, NULL);
    for(int i = 0; i < q; i++){
        char *mark = (char *) malloc(2 * sizeof (char));
        scanf("%s", mark);
        if(mark[0] == 'I'){
            int index = 0;
            scanf("%d", &index);
            char *t = (char *) malloc(100005 * sizeof (char));
            scanf("%s", t);
            int len = (int)strlen(t);
            node *ptr = head;
            int sum = 0;
            int idx = 0;
            while(1) {
                if (ptr->len + sum < index) {
                    sum += ptr->len;
                    ptr = ptr->next;
                } else {
                    idx = index - sum - 1;
                    break;
                }
            }
            if(idx == ptr->len - 1){
                adding(t, &ptr, ptr->next);
            } else{
                node *p = head;
                node *ptr1 = (node *) malloc(sizeof (node));
                ptr1->len = idx + 1;
                for(int j = 0; j <= idx; j++){
                    ptr1->s[i] = ptr->s[i];
                }
                node *ptr2 = (node *) malloc(sizeof (node));
                ptr2->len = ptr->len - ptr1->len;
                for(int j = 0; j < ptr2->len; j++){
                    ptr2->s[j] = ptr->s[j + idx + 1];
                }
                if(ptr == head){
                    head = ptr1;
                } else{
                    while(p){
                        if(p->next == ptr){
                            break;
                        }
                        p = p->next;
                    }
                    p->next = ptr1;
                }
                ptr2->next = ptr->next;
                ptr1->next = ptr2;
                free(ptr);
                adding(t, &ptr1, ptr2);
                if(len < B){
                    if(ptr1->len + len + ptr2->len <= B){
                        node *r = (node *) malloc(sizeof(node));
                        r->len = ptr1->len + len + ptr2->len;
                        r->next = ptr2->next;
                        for(int j = 0; j < ptr1->len; j++){
                            r->s[j] = ptr1->s[j];
                        }
                        for(int j = 0; j < len; j++){
                            r->s[ptr1->len + j] = t[j];
                        }
                        for(int j = 0; j < ptr2->len; j++){
                            r->s[ptr1->len + len + j] = ptr2->s[j];
                        }
                        if(ptr1 == head){
                            head = r;
                        } else{
                            p->next = r;
                        }
                        free(ptr1);
                    } else if(ptr1->len + len <= B){
                        node *r = (node *) malloc(sizeof(node));
                        r->len = ptr1->len + len;
                        r->next = ptr2;
                        for(int j = 0; j < ptr1->len; j++){
                            r->s[j] = ptr1->s[j];
                        }
                        for(int j = 0; j < len; j++){
                            r->s[ptr1->len + j] = t[j];
                        }
                        if(ptr1 == head){
                            head = r;
                        } else{
                            p->next = r;
                        }
                        free(ptr1);
                    } else if(ptr2->len + len <= B){
                        node *r = (node *) malloc(sizeof(node));
                        r->next = ptr2->next;
                        for(int j = 0; j < len; j++){
                            r->s[j] = t[j];
                        }
                        for(int j = 0; j < ptr2->len; j++){
                            r->s[len + j] = ptr2->s[j];
                        }
                        ptr1->next = r;
                    }
                } else if(len > B){
                    node *m = ptr1->next;
                    node *f = ptr1;
                    while(m){
                        if(m->next == ptr2){
                            break;
                        }
                        f = m;
                        m = m->next;
                    }
                    if(m->len + ptr2->len <= B){
                        node *r = (node *) malloc(sizeof(node));
                        r->next = ptr2->next;
                        r->len = m->len + ptr2->len;
                        for(int j = 0; j < m->len; j++){
                            r->s[j] = m->s[j];
                        }
                        for(int j = 0; j < ptr2->len; j++){
                            r->s[m->len + j] = ptr2->s[j];
                        }
                        f->next = r;
                    }
                }
            }
        } else{
            int index = 0;//真正下标:index - 1 第index个
            scanf("%d", &index);
            node *ptr = head;
            int sum = 0;
            int idx = 0;
            while(1) {
                if (ptr->len + sum < index) {
                    sum += ptr->len;
                    ptr = ptr->next;
                } else {
                    idx = index - sum - 1;
                    break;
                }
            }
            printf("%c\n", ptr->s[idx]);
        }
    }

    return 0;
}

void adding(char *s, node **bf, node *nt){
    int len = (int)strlen(s);
    if(len > B){
        node *add = (node *) malloc(sizeof(node));
        add->len = B;
        for(int i = 0; i < B; i++){
            add->s[i] = s[i];
        }
        add->next = NULL;
        if(*bf == NULL){
            *bf = add;
        } else{
            (*bf)->next = add;
        }
        adding(s + B, &add, nt);
    } else{
        node *add = (node *) malloc(sizeof(node));
        add->len = len;
        for(int i = 0; i < len; i++){
            add->s[i] = s[i];
        }
        add->next = nt;
        if(*bf == NULL){
            *bf = add;
        } else{
            (*bf)->next = add;
        }
    }
}