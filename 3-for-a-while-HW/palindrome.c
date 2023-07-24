//
// Created by 25378 on 2022/10/15.
//
#include <stdio.h>

int main(void)
{
    int n;

    scanf("%d",&n);

    getchar();

    char str[100201] = {0};
    char clone[100201] = {0};

    for(int i = 1; i <= n; i++){
        scanf("%c", &str[i]);
    }

    for(int i = 1; i <= n; i++){
        clone[i] = str[i];
    }

    int sum = 0;
    int t;
    for(int j = 1; j <= n / 2; j++){
        if(str[j] == '?' && str[n + 1 - j] != '?'){
            str[j] = str[n + 1 - j];
            clone[j] = str[j];
        } else if(str[j] != '?' && str[n + 1 - j] == '?'){
            str[n + 1 - j] = str[j];
            clone[n + 1 - j] = str[n + 1 - j];
        } else if(str[j] == '?' && str[n + 1 - j] == '?'){
            for(int k = j + 1; k <= n; k++){
                str[k + 1] = clone[k];
            }
            for(int i = 1; i <= n + 1; i++){
                clone[i] = str[i];
            }
            for(int p = n + 3 - j; p <= n + 1 ; p++){
                str[p + 1] = clone[p];
            }
            if(sum < 10){
                str[j] = '0';
                str[j + 1] = (char)((int)('0') + sum);
                str[n + 2 - j] = str[j + 1];
                str[n + 3 - j] = str[j];
            }
            if(sum >= 10){
                str[j] = (char)((int)('0') + (sum / 10));
                str[j + 1] = (char)((int)('0') + (sum % 10));
                str[n + 2 - j] = str[j + 1];
                str[n + 3 - j] = str[j];
            }
            for(int i = 1; i <= n + 2; i++){
                clone[i] = str[i];
            }
            sum ++;
            n = n + 2;
        }
    }

    for(int i = 1; i <= n; i++){
        printf("%c", str[i]);
    }

    return 0;
}

