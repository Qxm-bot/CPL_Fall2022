//
// Created by 25378 on 2022/10/22.
//
#include<stdio.h>

int main(void) {
    int n = 0;

    scanf("%d", &n);
    getchar();

    char life[1006] = {'\0'};
    for (int i = 0; i < 1006; i++) {
        life[i] = '.';
    }

    int len = -1;
    while (scanf("%c", &life[++len + 3]) != EOF);

    char copy[1006] = {'\0'};
    for (int i = 0; i < 1006; i++) {
        copy[i] = life[i];
    }

    int count = 0;
    int sum_of_A = 0;
    int sum_of_B = 0;
    while (count < n) {
        for (int i = 3; i < len + 3; i++) {
            if (copy[i] == '.') {
                for (int j = i - 3; j <= i + 3; j++) {
                    if (copy[j] == 'A') {
                        sum_of_A++;
                    } else if (copy[j] == 'B') {
                        sum_of_B++;
                    }
                }
                if (sum_of_B >= 2 && sum_of_B <= 4 && sum_of_A == 0) {
                    life[i] = 'B';
                }
                if (sum_of_A >= 2 && sum_of_A <= 4 && sum_of_B == 0) {
                    life[i] = 'A';
                }
            } else if (copy[i] == 'A') {
                for (int j = i - 3; j <= i + 3; j++) {
                    if (copy[j] == 'A') {
                        sum_of_A++;
                    } else if (copy[j] == 'B') {
                        sum_of_B++;
                    }
                }
                if (sum_of_B != 0 || sum_of_A >= 6 || sum_of_A <= 2) {
                    life[i] = '.';
                }
            } else if (copy[i] == 'B') {
                for (int j = i - 3; j <= i + 3; j++) {
                    if (copy[j] == 'A') {
                        sum_of_A++;
                    } else if (copy[j] == 'B') {
                        sum_of_B++;
                    }
                }
                if (sum_of_A != 0 || sum_of_B >= 6 || sum_of_B <= 2) {
                    life[i] = '.';
                }
            }
            sum_of_A = 0;
            sum_of_B = 0;
        }
        for (int i = 0; i < 1006; i++) {
            copy[i] = life[i];
        }
        count++;
    }

    for (int i = 3; i < len + 3; i++) {
        printf("%c", life[i]);
    }

    return 0;
}