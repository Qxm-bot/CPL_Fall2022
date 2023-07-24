//
// Created by 25378 on 2022/12/28.
//
#include <stdio.h>
int record_white[400][2] = {0};
int count_num_of_lct_white = 0;
int record_black[400][2] = {0};
int count_num_of_lct_black = 0;
void IsBlackFour(int i, int j, char board[20][20]); //return number of locations to win
void IsWhiteFour(int i, int j, char board[20][20]);
int main(void){
    int T = 0;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        char board[20][20] = {0};
        int judge = 0;

        for(int j = 0; j < 20; j++){
            /*for(int k = 0; k < 20; k++){
                scanf("%c", &board[j][k]);
            }*/
            scanf("%s", board[j]);
            /*if(i != T - 1 || j != 19){
                getchar();
            }*/
        }
        for(int j = 0; j <= 15; j++){
            for(int k = 0; k <= 15; k++){
                IsWhiteFour(j, k, board);
                IsBlackFour(j, k, board);
            }
        }
        if(count_num_of_lct_white >= 1){
            judge = 1;
        } else if(count_num_of_lct_white == 0){
            if(count_num_of_lct_black <= 1){
                judge = 0;
            } else if(count_num_of_lct_black >= 2){
                judge = 2;
            }
        }

        if(judge == 0){
            printf("Not Sure");
        } else if(judge == 1){
            printf("Lose");
        } else{
            printf("Win");
        }
        if(i != T - 1){
            printf("\n");
        }
        count_num_of_lct_white = 0;
        count_num_of_lct_black = 0;
    }
    return 0;
}

void IsBlackFour(int i, int j, char board[20][20]){
    //judge the line, get the location
    for(int k = i; k <= i + 4; k++){
        int num = 0;
        int t = 1;
        for(int m = j; m <= j + 4; m++){
            if(board[k][m] == '#'){
                num++;
            }
            if(board[k][m] == '*'){
                t = 0;
                break;
            }
            if(board[k][m] == '_'){
                record_black[count_num_of_lct_black][0] = k;
                record_black[count_num_of_lct_black][1] = m;
            }
        }
        if(num == 4 && t){
            if(count_num_of_lct_black == 0){
                count_num_of_lct_black++;
            } else {
                int repeat = 0;
                for (int y = 0; y < count_num_of_lct_black; y++) {
                    if (record_black[y][0] == record_black[count_num_of_lct_black][0]
                        && record_black[y][1] == record_black[count_num_of_lct_black][1]) {
                        repeat = 1;
                        break;
                    }
                }
                if(repeat == 0) {
                    count_num_of_lct_black++;
                }
            }
        }
    }
    //judge the col
    for(int k = j; k <= j + 4; k++){
        int num = 0;
        int t = 1;
        for(int m = i; m <= i + 4; m++){
            if(board[m][k] == '#'){
                num++;
            }
            if(board[m][k] == '*'){
                t = 0;
                break;
            }
            if(board[m][k] == '_'){
                record_black[count_num_of_lct_black][0] = m;
                record_black[count_num_of_lct_black][1] = k;
            }
        }
        if(num == 4 && t){
            if(count_num_of_lct_black == 0){
                count_num_of_lct_black++;
            } else {
                int repeat = 0;
                for (int y = 0; y < count_num_of_lct_black; y++) {
                    if (record_black[y][0] == record_black[count_num_of_lct_black][0]
                        && record_black[y][1] == record_black[count_num_of_lct_black][1]) {
                        repeat = 1;
                        break;
                    }
                }
                if (repeat == 0) {
                    count_num_of_lct_black++;
                }
            }
        }
    }
    //判断斜着的
    int number = 0;
    int t1 = 1;
    for(int k = i; k <= i + 4; k++){
        if(board[k][k - i + j] == '#'){
            number++;
        }
        if(board[k][k - i + j] == '*'){
            t1 = 0;
            break;
        }
        if(board[k][k - i + j] == '_'){
            record_black[count_num_of_lct_black][0] = k;
            record_black[count_num_of_lct_black][1] = k - i + j;
        }
    }
    if(number == 4 && t1){
        if(count_num_of_lct_black == 0){
            count_num_of_lct_black++;
        } else {
            int repeat = 0;
            for (int y = 0; y < count_num_of_lct_black; y++) {
                if (record_black[y][0] == record_black[count_num_of_lct_black][0]
                    && record_black[y][1] == record_black[count_num_of_lct_black][1]) {
                    repeat = 1;
                    break;
                }
            }
            if (repeat == 0) {
                count_num_of_lct_black++;
            }
        }
    }
    number = 0;
    int t2 = 1;
    for(int k = i; k <= i + 4; k++){
        if(board[k][j + 4 - k + i] == '#'){
            number++;
        }
        if(board[k][j + 4 - k + i] == '*'){
            t2 = 0;
            break;
        }
        if(board[k][j + 4 - k + i] == '_'){
            record_black[count_num_of_lct_black][0] = k;
            record_black[count_num_of_lct_black][1] = j + 4 - k + i;
        }
    }
    if(number == 4 && t2){
        if(count_num_of_lct_black == 0){
            count_num_of_lct_black++;
        } else {
            int repeat = 0;
            for (int y = 0; y < count_num_of_lct_black; y++) {
                if (record_black[y][0] == record_black[count_num_of_lct_black][0]
                    && record_black[y][1] == record_black[count_num_of_lct_black][1]) {
                    repeat = 1;
                    break;
                }
            }
            if (repeat == 0) {
                count_num_of_lct_black++;
            }
        }
    }
}

void IsWhiteFour(int i, int j, char board[20][20]){
    //judge the line, get the location
    for(int k = i; k <= i + 4; k++){
        int num = 0;
        int t = 1;
        for(int m = j; m <= j + 4; m++){
            if(board[k][m] == '*'){
                num++;
            }
            if(board[k][m] == '#'){
                t = 0;
                break;
            }
            if(board[k][m] == '_'){
                record_white[count_num_of_lct_white][0] = k;
                record_white[count_num_of_lct_white][1] = m;
            }
        }
        if(num == 4 && t){
            if(count_num_of_lct_white == 0){
                count_num_of_lct_white++;
            } else {
                int repeat = 0;
                for (int y = 0; y < count_num_of_lct_white; y++) {
                    if (record_white[y][0] == record_white[count_num_of_lct_white][0]
                        && record_white[y][1] == record_white[count_num_of_lct_white][1]) {
                        repeat = 1;
                        break;
                    }
                }
                if (repeat == 0) {
                    count_num_of_lct_white++;
                }
            }
        }
    }
    //judge the col
    for(int k = j; k <= j + 4; k++){
        int num = 0;
        int t = 1;
        for(int m = i; m <= i + 4; m++){
            if(board[m][k] == '*'){
                num++;
            }
            if(board[m][k] == '#'){
                t = 0;
                break;
            }
            if(board[m][k] == '_'){
                record_white[count_num_of_lct_white][0] = m;
                record_white[count_num_of_lct_white][1] = k;
            }
        }
        if(num == 4 && t){
            if(count_num_of_lct_white == 0){
                count_num_of_lct_white++;
            } else {
                int repeat = 0;
                for (int y = 0; y < count_num_of_lct_white; y++) {
                    if (record_white[y][0] == record_white[count_num_of_lct_white][0]
                        && record_white[y][1] == record_white[count_num_of_lct_white][1]) {
                        repeat = 1;
                        break;
                    }
                }
                if (repeat == 0) {
                    count_num_of_lct_white++;
                }
            }
        }
    }
    //判断斜着的
    int number = 0;
    int t1 = 1;
    for(int k = i; k <= i + 4; k++){
        if(board[k][k - i + j] == '*'){
            number++;
        }
        if(board[k][k - i + j] == '#'){
            t1 = 0;
            break;
        }
        if(board[k][k - i + j] == '_'){
            record_white[count_num_of_lct_white][0] = k;
            record_white[count_num_of_lct_white][1] = k - i + j;
        }
    }
    if(number == 4 && t1){
        if(count_num_of_lct_white == 0){
            count_num_of_lct_white++;
        } else {
            int repeat = 0;
            for (int y = 0; y < count_num_of_lct_white; y++) {
                if (record_white[y][0] == record_white[count_num_of_lct_white][0]
                    && record_white[y][1] == record_white[count_num_of_lct_white][1]) {
                    repeat = 1;
                    break;
                }
            }
            if (repeat == 0) {
                count_num_of_lct_white++;
            }
        }
    }
    number = 0;
    int t2 = 1;
    for(int k = i; k <= i + 4; k++){
        if(board[k][j + 4 - k + i] == '*'){
            number++;
        }
        if(board[k][j + 4 - k + i] == '#'){
            t2 = 0;
            break;
        }
        if(board[k][j + 4 - k + i] == '_'){
            record_white[count_num_of_lct_white][0] = k;
            record_white[count_num_of_lct_white][1] = j + 4 - k + i;
        }
    }
    if(number == 4 && t2){
        if(count_num_of_lct_white == 0){
            count_num_of_lct_white++;
        } else {
            int repeat = 0;
            for (int y = 0; y < count_num_of_lct_white; y++) {
                if (record_white[y][0] == record_white[count_num_of_lct_white][0]
                    && record_white[y][1] == record_white[count_num_of_lct_white][1]) {
                    repeat = 1;
                    break;
                }
            }
            if (repeat == 0) {
                count_num_of_lct_white++;
            }
        }
    }
}