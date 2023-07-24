//
// Created by 25378 on 2022/12/9.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Player{
    char *name;
    int offense;
    int defense;
    int org;
} player;

typedef struct Team{
    char *name;
    player players[11];
    double avr_offense;
    double avr_defense;
    double avr_org;
} team;

int main(void){
    int n;
    scanf("%d", &n);
    team tm[1000] = {0};
    int count = 0;
    for(int j = 0; j < n; j++){
        tm[j].name = (char*) malloc(21 * sizeof (char));
        for(int k = 0; k < 11; k++){
            tm[j].players[k].name = (char*) malloc(21 *sizeof (char));
        }
    }
    while(count != n){
        double total_offense = 0.0;
        double total_defense = 0.0;
        double total_org = 0.0;
        scanf("%s", tm[count].name);
        for(int i = 0; i < 11; i++){
            scanf("%s", tm[count].players[i].name);
            scanf("%d%d%d",
                  &tm[count].players[i].offense,
                  &tm[count].players[i].defense,
                  &tm[count].players[i].org);
            total_offense += tm[count].players[i].offense;
            total_defense += tm[count].players[i].defense;
            total_org += tm[count].players[i].org;
        }
        tm[count].avr_offense = total_offense / 11;
        tm[count].avr_defense = total_defense / 11;
        tm[count].avr_org = total_org / 11;
        count++;
    }

    int sort[1000] = {0};
    //offense_sort
    for(int i = 0; i < n; i++){
        sort[i] = i;
    }
    int t = 0;
    while(t != n - 1){
        for(int i = n - 1; i >= t + 1; i--){
            if(tm[i].avr_offense > tm[i - 1].avr_offense){
                double exchange = tm[i].avr_offense;
                tm[i].avr_offense = tm[i - 1].avr_offense;
                tm[i - 1].avr_offense = exchange;
                int exchange_2 = sort[i];
                sort[i] = sort[i - 1];
                sort[i - 1] = exchange_2;
            }
        }
        t++;
    }
    for(int i = 0; i < n; i++){
        printf("%s ", tm[sort[i]].name);
    }
    printf("\n");

    //defense_sort
    for(int i = 0; i < n; i++){
        sort[i] = i;
    }
    t = 0;
    while(t != n - 1){
        for(int i = n - 1; i >= t + 1; i--){
            if(tm[i].avr_defense > tm[i - 1].avr_defense){
                double exchange = tm[i].avr_defense;
                tm[i].avr_defense = tm[i - 1].avr_defense;
                tm[i - 1].avr_defense = exchange;
                int exchange_2 = sort[i];
                sort[i] = sort[i - 1];
                sort[i - 1] = exchange_2;
            }
        }
        t++;
    }
    for(int i = 0; i < n; i++){
        printf("%s ", tm[sort[i]].name);
    }
    printf("\n");

    //org_sort
    for(int i = 0; i < n; i++){
        sort[i] = i;
    }
    t = 0;
    while(t != n - 1){
        for(int i = n - 1; i >= t + 1; i--){
            if(tm[i].avr_org > tm[i - 1].avr_org){
                double exchange = tm[i].avr_org;
                tm[i].avr_org = tm[i - 1].avr_org;
                tm[i - 1].avr_org = exchange;
                int exchange_2 = sort[i];
                sort[i] = sort[i - 1];
                sort[i - 1] = exchange_2;
            }
        }
        t++;
    }
    for(int i = 0; i < n; i++){
        printf("%s ", tm[sort[i]].name);
    }

    for(int j = 0; j < n; j++){
        free(tm[j].name);
        for(int k = 0; k < 11; k++){
            free(tm[j].players[k].name);
        }
    }

    return 0;
}
