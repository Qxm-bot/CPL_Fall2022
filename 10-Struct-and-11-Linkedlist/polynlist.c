//
// Created by 25378 on 2022/12/9.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct poly {
    int power;
    char name[11];
    int cft[20000];
}Poly;

Poly p1;
Poly p2;
Poly plus;
Poly minus;
Poly multiply;

void print_poly(Poly p);
int main(void){
    scanf("%d%d", &p1.power, &p2.power);
    char *string = (char*) malloc(20 * sizeof (char));
    scanf("%s", string);
    int len = (int)strlen(string);
    for(int i = 0; i <= len; i++){
        p1.name[i] = *(string + i);
        p2.name[i] = *(string + i);
        plus.name[i] = *(string + i);
        minus.name[i] = *(string + i);
        multiply.name[i] = *(string + i);
    }
    for(int i = p1.power; i >= 0; i--){
        scanf("%d", &p1.cft[i]);
    }
    for(int i = p2.power; i >= 0; i--){
        scanf("%d", &p2.cft[i]);
    }

    //print plus
    if(p2.power >= p1.power){
        plus.power = p2.power;
        for (int i = p2.power; i > p1.power; i--) {
            plus.cft[i] = p2.cft[i];
        }
        for(int i = p1.power; i >= 0; i--){
            plus.cft[i] = p1.cft[i] + p2.cft[i];
        }
        print_poly(plus);
        printf("\n");
    } else if(p2.power < p1.power){
        plus.power = p1.power;
        for(int i = p1.power; i > p2.power; i--){
            plus.cft[i] = p1.cft[i];
        }
        for(int i = p2.power; i >= 0; i--){
            plus.cft[i] = p1.cft[i] + p2.cft[i];
        }
        print_poly(plus);
        printf("\n");
    }

    //print minus
    if(p2.power >= p1.power){
        minus.power = p2.power;
        for(int i = p2.power; i > p1.power; i--){
            minus.cft[i] = -p2.cft[i];
        }
        for(int i = p1.power; i >= 0; i--){
            minus.cft[i] = p1.cft[i] - p2.cft[i];
        }
        print_poly(minus);
        printf("\n");
    } else if(p2.power < p1.power){
        minus.power = p1.power;
        for(int i = p1.power; i > p2.power; i--){
            minus.cft[i] = p1.cft[i];
        }
        for(int i = p2.power; i >= 0; i--){
            minus.cft[i] = p1.cft[i] - p2.cft[i];
        }
        print_poly(minus);
        printf("\n");
    }

    //print multiply
    multiply.power = p1.power + p2.power;
    if(p1.power >= p2.power) {
        for (int i = multiply.power; i >= 0; i--) {
            multiply.cft[i] = 0;
            if (i >= p1.power) {
                for (int j = p1.power; j >= i - p2.power; j--) {
                    multiply.cft[i] += p1.cft[j] * p2.cft[i - j];
                }
            } else if(i < p1.power && i >= p2.power){
                for(int j = i; j >= i - p2.power; j--){
                    multiply.cft[i] += p1.cft[j] * p2.cft[i - j];
                }
            } else if(i < p2.power){
                for(int j = i; j >= 0; j--){
                    multiply.cft[i] += p1.cft[j] * p2.cft[i - j];
                }
            }
        }
    } else {
        for (int i = multiply.power; i >= 0; i--) {
            multiply.cft[i] = 0;
            if (i >= p2.power) {
                for (int j = p2.power; j >= i - p1.power; j--) {
                    multiply.cft[i] += p2.cft[j] * p1.cft[i - j];
                }
            } else if(i < p2.power && i >= p1.power){
                for(int j = i; j >= i - p1.power; j--){
                    multiply.cft[i] += p2.cft[j] * p1.cft[i - j];
                }
            } else if(i < p1.power){
                for(int j = i; j >= 0; j--){
                    multiply.cft[i] += p2.cft[j] * p1.cft[i - j];
                }
            }
        }
    }
    print_poly(multiply);

    free(string);

    return 0;
}

void print_poly(Poly p){
    if(p.power == 1){
        if(p.cft[p.power] == 1){
            printf("%s", p.name);
        } else{
            printf("%d%s", p.cft[p.power], p.name);
        }
    } else if(p.cft[p.power] == 1){
        printf("%s^%d", p.name, p.power);
    } else if(p.cft[p.power] == -1){
        printf("-%s^%d", p.name, p.power);
    } else {
        printf("%d%s^%d", p.cft[p.power], p.name, p.power);
    }

    for(int i = p.power - 1; i >= 0; i--){
        if(p.cft[i] > 0) {
            if (i == 0) {
                printf("+%d", p.cft[i]);
            } else if (i == 1) {
                if(p.cft[i] == 1){
                    printf("+%s", p.name);
                } else{
                    printf("+%d%s", p.cft[i], p.name);
                }
            } else{
                if(p.cft[i] == 1){
                    printf("+%s^%d", p.name, i);
                } else{
                    printf("+%d%s^%d", p.cft[i], p.name, i);
                }
            }
        } else if(p.cft[i] < 0){
            if (i == 0) {
                printf("%d", p.cft[i]);
            } else if (i == 1) {
                if(p.cft[i] == -1){
                    printf("-%s", p.name);
                } else{
                    printf("%d%s", p.cft[i], p.name);
                }
            } else{
                if(p.cft[i] == -1){
                    printf("-%s^%d", p.name, i);
                } else{
                    printf("%d%s^%d", p.cft[i], p.name, i);
                }
            }
        }
    }
}