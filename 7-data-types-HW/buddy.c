//
// Created by 25378 on 2022/11/18.
//
#include <stdio.h>
#include <math.h>

int store_num[10001] = {1};
int distribute[10050] = {0};
int next[10050] = {0};
int operate[2] = {0};
int size[10050] = {0};
int mark_2 = 0;
int m = 1;
int point_of_division = 0;
int count = 0;

int decide_ask_for_size(int input);

int main(void) {
    int n = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    size[1] = (int) pow(2.0, n);
    char get_the_input;
    while (count < q) {
        getchar();
        scanf("%c", &get_the_input);
        if (get_the_input == 'A') {
            scanf("%d%d", &operate[0], &operate[1]);
            count++;
            int mark = 1;
            int i = 1;
            store_num[m] = store_num[m - 1];
            while (i != 0) {
                if (distribute[i] == 0 && size[i] == decide_ask_for_size(operate[1])) {
                    distribute[i] = operate[0];
                    mark = 0;
                    break;
                }
                i = next[i];
            }
            if (mark) {
                i = 1;
                while (i != 0) {
                    if (distribute[i] == 0 && size[i] > decide_ask_for_size(operate[1])) {
                        store_num[m]++;
                        int exchange = next[i];
                        next[i] = store_num[m];
                        next[store_num[m]] = exchange;
                        size[i] = size[i] / 2;
                        size[store_num[m]] = size[i];
                        point_of_division = i;
                        break;
                    }
                    i = next[i];
                }
                mark_2 = 1;
            }
            while (mark_2) {
                if (size[point_of_division] == decide_ask_for_size(operate[1])) {
                    distribute[point_of_division] = operate[0];
                    mark_2 = 0;
                    break;
                }
                store_num[m]++;
                int exchange = next[point_of_division];
                next[point_of_division] = store_num[m];
                next[store_num[m]] = exchange;
                size[point_of_division] = size[point_of_division] / 2;
                size[store_num[m]] = size[point_of_division];
            }
            mark_2 = 0;
            point_of_division = 0;
            m++;
        } else if (get_the_input == 'Q') {
            if (m == 1) {
                printf("%d\n", store_num[0]);
                printf("0\n");
            }
            if (m >= 2) {
                printf("%d\n", store_num[m - 1]);
                int j = 1;
                while (j != 0) {
                    printf("%d ", distribute[j]);
                    j = next[j];
                }
                printf("\n");
            }
            count++;
        }
    }
    return 0;
}

int decide_ask_for_size(int input) {
    if (input == 1) {
        return 1;
    }
    int i = 0;
    while (input <= (int) pow(2.0, i) || input > (int) pow(2.0, i + 1)) {
        i++;
    }
    return (int) pow(2.0, i + 1);
}


