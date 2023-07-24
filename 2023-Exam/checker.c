//
// Created by 25378 on 2023/2/19.
//
#include <stdio.h>
#include <string.h>

int main()
{
    int T = 0;
    scanf("%d", &T);
    char s[100005];
    char t[200005];
    for (int i = 0; i < T; i++)
    {
        int n = 0;
        scanf("%d%s%s", &n, s, t);
        int isWrong = 0;
        int len = (int)strlen(t);

        for (int j = 0; j <= (len - 1) / 2; j++)
        {
            if (t[j] != t[len - 1 - j] || (!(t[j] <= 'Z' && t[j] >= 'A') && !(t[j] <= 'z' && t[j] >= 'a') && !(t[j] <= '9' && t[j] >= '0')))
            {
                isWrong = 1;
                break;
            }
        }
        int record[100] = {0};
        int k = 0;
        if (!isWrong)
        {
            for (int j = 0; j <= n; j++)
            {
                if (s[j] != '?')
                {
                    if (s[j] == t[k])
                    {
                        k++;
                    }
                    else
                    {
                        isWrong = 1;
                        break;
                    }
                }
                else if (s[j] == '?' && s[n - 1 - j] == '?')
                {
                    if (!((t[k] <= '9' && t[k] >= '0') || !(t[k + 1] <= '9' && t[k + 1] >= '0')))
                    {
                        isWrong = 1;
                        break;
                    }
                    else
                    {
                        if (j <= (n - 1) / 2)
                        {
                            int num1 = (t[k] - '0') * 10 + t[k + 1] - '0';
                            int num2 = t[k] - '0' + (t[k + 1] - '0') * 10;
                            if (record[num1] == 0)
                            {
                                record[num1] = 1;
                                k += 2;
                            }
                            else if (record[num2] == 0)
                            {
                                record[num2] = 1;
                                k += 2;
                            }
                            else
                            {
                                isWrong = 1;
                                break;
                            }
                        }
                        else
                        {
                            k += 2;
                        }
                    }
                }
                else if (s[j] == '?')
                {
                    if (t[k] != s[n - 1 - j])
                    {
                        isWrong = 1;
                        break;
                    }
                    else
                    {
                        k++;
                    }
                }
            }
        }

        if (isWrong)
        {
            printf("Wrong Answer!\n");
        }
        else
        {
            printf("Correct.\n");
        }
    }

    return 0;
}
