//
// Created by 25378 on 2022/10/14.
//
#include <stdio.h>

int main(void) {
    int n;

    scanf("%d", &n);

    getchar();

    char a[1000];

    for (int i = 0; i < n; i++) {
        scanf("%c", &a[i]);
    }

    int b[123] = {0};

    //计算每个字母的个数
    for (int j = 0; j < n; j++) {
        b[(int) a[j]]++;
    }

    //计算个数的最大值
    int max_of_b = b[(int) a[0]];
    for (int k = 1; k < n; k++) {
        if (b[(int) a[k]] > max_of_b) {
            max_of_b = b[(int) a[k]];
        }
    }

    //分别统计大写和小写字母数量
    int num_of_capital = 0;
    int num_of_small = 0;
    for (int i = 65; i < 123; i++) {
        if (b[i] != 0) {
            i < 91 ? num_of_capital++ : num_of_small++;
        }
    }

    //统计大小写都有的字母的数量
    int c[123] = {0};
    for (int i = 0; i < n; i++) {
        if ((int) a[i] > 96) {
            for (int p = 0; p < n; p++) {
                if ((int) a[p] == (int) a[i] - 32) {
                    c[(int) a[i]] = 1;
                    break;
                }
            }
        }
    }
    int sum = 0;
    for (int j = 0; j < 123; j++) {
        if (c[j] == 1) {
            sum++;
        }
    }

    //输出“=”
    for (int k = max_of_b; k >= 1; k--) {
        for (int i = 'a'; i <= 'z'; i++) {
            if (b[i] != 0 || b[i - 32] != 0) {
                if (c[i] == 1) {
                    if (b[i] >= k && b[i - 32] >= k) {
                        printf("== ");
                    } else if (b[i] >= k && b[i - 32] < k) {
                        printf("=  ");
                    } else if (b[i] < k && b[i - 32] >= k) {
                        printf(" = ");
                    } else if (b[i] < k && b[i - 32] < k) {
                        printf("   ");
                    }
                } else if (b[i] != 0) {
                    if (b[i] >= k) {
                        printf("= ");
                    } else {
                        printf("  ");
                    }
                } else if (b[i - 32] != 0) {
                    if (b[i - 32] >= k) {
                        printf("= ");
                    } else {
                        printf("  ");
                    }
                }
            }
        }
        printf("\n");
    }

    //输出分割线
    for (int i = 1; i <= 2 * num_of_small + 2 * num_of_capital - 1 - sum; i++) {
        printf("-");
    }
    printf("\n");

    //输出字母
    for (int i = 'a'; i <= 'z'; i++) {
        if (b[i] != 0) {
            if (c[i] == 1) {
                printf("%c%c ", (char) i, (char) (i - 32));
            } else {
                printf("%c ", (char) i);
            }
        } else if (b[i - 32] != 0) {
            printf("%c ", (char) (i - 32));
        }
    }

    return 0;
}
