//
// Created by 25378 on 2022/12/10.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    char *name;
    int _len;
    struct node *contain[10000];
    char *belong_to;
} Node;

int count(Node *position);

void Free(Node **head);

int main(void) {
    Node *record[10000];
    int len_of_record = 0;
    int n = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    char *s1[10000] = {0};
    char *s2[10000] = {0};

    Node *head = (Node *) malloc(sizeof(Node));
    for (int i = 0; i < n; i++) {
        s1[i] = (char *) malloc(11 * sizeof(char));
        s2[i] = (char *) malloc(11 * sizeof(char));
        scanf("%s", s1[i]);
        scanf("%s", s2[i]);
        if (strcmp(s2[i], "~~~") == 0) {
            head->name = s1[i];
            head->_len = 0;
            head->belong_to = NULL;
        } else {
            record[len_of_record] = (Node *) malloc(sizeof(Node));
            record[len_of_record]->name = s1[i];
            record[len_of_record]->_len = 0;
            record[len_of_record]->belong_to = s2[i];
            len_of_record++;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        if (strcmp(record[i]->belong_to, head->name) == 0) {
            head->contain[head->_len] = record[i];
            head->_len++;
        } else {
            for (int j = 0; j < n - 1; j++) {
                if (strcmp(record[i]->belong_to, record[j]->name) == 0) {
                    record[j]->contain[record[j]->_len] = record[i];
                    record[j]->_len++;
                    break;
                }
            }
        }
    }

    char *string1 = (char *) malloc(7 * sizeof(char));
    char *string2 = (char *) malloc(13 * sizeof(char));
    for (int i = 0; i < q; i++) {
        scanf("%s", string1);
        scanf("%s", string2);
        if (strcmp(string1, "remove") == 0) {
            if (strcmp(string2, head->name) == 0) {
                for (int k = 0; k < head->_len; k++) {
                    Free(&(head->contain[k]));
                }
                Node *store = head;
                head = NULL;
                free(store);
            } else {
                for (int j = 0; j < n - 1; j++) {
                    if (record[j] != NULL) {
                        if (strcmp(record[j]->name, string2) == 0) {
                            if (record[j]->_len != 0) {
                                for (int k = 0; k < record[j]->_len; k++) {
                                    Free(&(record[j]->contain[k]));
                                }
                            }

                            if (strcmp(record[j]->belong_to, head->name) == 0) {
                                for (int t = 0; t < head->_len; t++) {
                                    if (head->contain[t] == record[j]) {
                                        Node *store = record[j];
                                        head->contain[t] = NULL;
                                        record[j] = NULL;
                                        free(store);
                                        break;
                                    }
                                }
                                break;
                            } else {
                                int r1 = 0;
                                int r2 = 0;
                                for (int x = 0; x < n - 1; x++) {
                                    if (record[x] != NULL) {
                                        if (strcmp(record[x]->name, record[j]->belong_to) == 0) {
                                            for (int p = 0; p < record[x]->_len; p++) {
                                                if (record[j] == record[x]->contain[p]) {
                                                    r1 = x;
                                                    r2 = p;
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                                Node *store = record[j];
                                record[r1]->contain[r2] = NULL;
                                record[j] = NULL;
                                free(store);
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            if (strcmp(string2, head->name) == 0) {
                printf("%d\n", count(head));
            } else {
                for (int j = 0; j < n - 1; j++) {
                    if (record[j] != NULL) {
                        if (strcmp(record[j]->name, string2) == 0) {
                            printf("%d\n", count(record[j]));
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(s1[i]);
        free(s2[i]);
    }
    Free(&head);
    free(string1);
    free(string2);
    return 0;
}

int count(Node *position) {
    if (position == NULL) {
        return 0;
    } else {
        int num = 1;
        for (int i = 0; i < position->_len; i++) {
            num += count(position->contain[i]);
        }
        return num;
    }
}

void Free(Node **head) {
    if (*head == NULL) {
        return;
    } else {
        if ((*head)->_len == 0) {
            Node *store = *head;
            *head = NULL;
            free(store);
        } else {
            for (int i = 0; i < (*head)->_len; i++) {
                Free(&((*head)->contain[i]));
            }
            Node *store = *head;
            *head = NULL;
            free(store);
        }
    }
}