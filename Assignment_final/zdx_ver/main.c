#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max2(a, b) ((a) > (b) ? (a) : (b))
#define letter 'a'
#define number '1'
int **Dp, MaxDP = 3300;
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}
int error2(char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(-1);
}
int initDP()
{
    int i;
    Dp = (int **)malloc(MaxDP * sizeof(int *));
    for (i = 0; i < MaxDP; i++)
        Dp[i] = (int *)malloc(MaxDP * sizeof(int));
    return 0;
}
int editdistDP(char *str1, char *str2)
{
    int i, j;
    int len1, len2;
    static int flag = 0;

    (flag++) ? 1 : initDP();
    len1 = strlen(str1) + 1;
    len2 = strlen(str2) + 1;
    (max2(len1, len2) >= MaxDP) ? error2("DP memory error!") : len1;
    for (i = 0; i <= len1; i++)
    {
        for (j = 0; j <= len2; j++)
        {
            if (i == 0)
                Dp[i][j] = j;
            else if (j == 0)
                Dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                Dp[i][j] = Dp[i - 1][j - 1];
            else
                Dp[i][j] = 1 + min3(Dp[i][j - 1], Dp[i - 1][j], Dp[i - 1][j - 1]);
        }
    }
    return Dp[len1][len2];
}
char type(int c)
{
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
    {
        return (letter);
    }
    else
        return (c);
}
int getword(char *s, FILE *fp)
{
    int c, i = 0;
    while (type(c = fgetc(fp)) != letter)
    {
        if (c == EOF)
        {
            return c;
        }
        else
            continue;
    }
    s[i++] = c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (type(c) != letter)
        {
            break;
        }
        s[i++] = c;
    }
    s[i] = '\0';
    return 1;
}
int getstream(char *s, FILE *fp)
{
    int c, i = 0;
    while (type(c = fgetc(fp)) != letter)
    {
        if (c == EOF)
        {
            return c;
        }
        if (c >= '0' && c <= '1')
        {
            s[i++] = c;
        }
    }
}
char s[100];
char line[2000];
char keyword[500][10];
char word[20];
char name[20][20];
char f1[] = "main";
char f2[] = "FUNC";
struct stream
{
    int n;
    char keystream[10000];
};
struct stream mainstream[50];
struct func
{
    int n;
    char function_name[20];
    char function_stream[2000];
};
struct func function[20];
int main()
{
    FILE *in, *key;
    in = fopen("codes.txt", "r");
    key = fopen("keepwords.txt", "r");
    int keepword = 0, keepstream = 0, range = 0;
    while (getword(s, key) != EOF)
    {
        strcpy(keyword[keepword], s);
        keepword++;
    }
    for (int i = 0; i < keepword; i++)
    {
        for (int j = i; j < keepword; j++)
        {
            if (strcmp(keyword[i], keyword[j]) > 0)
            {
                char S[20];
                strcpy(S, keyword[i]);
                strcpy(keyword[i], keyword[j]);
                strcpy(keyword[j], S);
            }
        }
    }
    int num = 1, place;
    while (fgets(line, 1024, in) != NULL)
    {
        int length, data = 0, state = 0, order = 0;
        length = strlen(line);
        if (length == 1)
        {
            continue;
        }
        for (int i = 0; i < length - 1; i++)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                continue;
            }
            else
            {
                state = 1;
                break;
            }
        }
        if (state == 0)
        {
            if (keepstream >= 1)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if (strcmp(name[i], function[j].function_name) == 0 && function[j].n == 0)
                        {
                            strcat(mainstream[keepstream - 1].keystream, function[j].function_stream);
                            function[j].n = 1;
                        }
                    }
                }
            }
            /*if(keepstream==1) {
                printf("%d\n",range);
                for(int i=0;i<range;i++) {
                    printf("%s\n%s\n",function[i].function_name,function[i].function_stream);
                }
            }*/
            for (int i = 0; i < 20; i++)
            {
                word[i] = '\0';
            }
            for (int i = 0; i < length - 1; i++)
            {
                data = data * 10 + line[i] - '0';
            }
            num = 1;
            range = 0;
            mainstream[keepstream++].n = data;
            for (int i = 0; i < 20; i++)
            {
                function[i].n = 0;
                for (int j = 0; j < 20; j++)
                {
                    function[i].function_name[j] = '\0';
                }
                for (int j = 0; j < 2000; j++)
                {
                    function[i].function_stream[j] = '\0';
                }
            }
            continue;
        } // 输入编号+整合数据流？
        int sign, flag = 0, notice = 0;
        sign = type(line[0]);
        if (sign == letter)
        {
            for (int i = 0; i < 20; i++)
            {
                word[i] = '\0';
            }
        }
        while (sign == letter)
        {
            word[flag] = line[flag];
            flag++;
            sign = type(line[flag]);
        }
        if (sign == '(')
        {
            for (int i = 0; i < keepword; i++)
            {
                if (strcmp(word, keyword[i]) == 0)
                {
                    notice = 1;
                    flag = 0;
                    break;
                }
            }
            if (strcmp(word, f1) == 0)
            {
                strcpy(function[0].function_name, word);
                function[0].n = 0;
                place = 0;
            }
            else if (notice == 0)
            {
                strcpy(function[num].function_name, word);
                place = num;
                num++;
            }
            while (line[flag] != ')')
            {
                flag++;
            }
            flag++;
        }
        else
        {
            flag = 0;
        } // 判断是否为函数名
        if (place == 0)
        {
            while (flag < length)
            {
                int c, d, e;
                c = type(line[flag]);
                d = type(line[flag - 1]);
                e = type(line[flag + 1]);
                if (c != letter)
                {
                    if (c != ' ' && c != '\n' && c != '\r' && c != '\t')
                    {
                        if (c >= '0' && c <= '9' && d != letter && e != letter)
                        {
                            int len = strlen(mainstream[keepstream - 1].keystream);
                            mainstream[keepstream - 1].keystream[len] = c;
                        }
                        else if (c < '0' || c > '9')
                        {
                            int len = strlen(mainstream[keepstream - 1].keystream);
                            mainstream[keepstream - 1].keystream[len] = c;
                        }
                    }
                }
                else if (c == letter)
                {
                    order = 0;
                    int k = 0;
                    for (int i = 0; i < 20; i++)
                    {
                        word[i] = '\0';
                    }
                    while (c == letter || c == '_')
                    {
                        word[order++] = line[flag];
                        flag++;
                        c = type(line[flag]);
                    }
                    for (int i = 0; i < keepword; i++)
                    {
                        if (strcmp(word, keyword[i]) == 0)
                        {
                            strcat(mainstream[keepstream - 1].keystream, word);
                            k = 1;
                        }
                    }
                    if (k == 0 && c == '(')
                    {
                        strcat(mainstream[keepstream - 1].keystream, f2);
                        strcpy(name[range], word);
                        range++;
                    }
                    flag--;
                }
                flag++;
            }
        }
        else if (place > 0)
        {
            while (flag < length)
            {
                int c, d, e;
                c = type(line[flag]);
                d = type(line[flag - 1]);
                e = type(line[flag + 1]);
                if (c != letter)
                {
                    if (c != ' ' && c != '\n' && c != '\r' && c != '\t')
                    {
                        if (c >= '0' && c <= '9' && d != letter && e != letter)
                        {
                            int len = strlen(function[place].function_stream);
                            function[place].function_stream[len] = c;
                        }
                        else if (c < '0' || c > '9')
                        {
                            int len = strlen(function[place].function_stream);
                            function[place].function_stream[len] = c;
                        }
                    }
                }
                else if (c == letter)
                {
                    order = 0;
                    int k = 0;
                    for (int i = 0; i < 20; i++)
                    {
                        word[i] = '\0';
                    }
                    while (c == letter || c == '_')
                    {
                        word[order++] = line[flag];
                        flag++;
                        c = type(line[flag]);
                    }
                    for (int i = 0; i < keepword; i++)
                    {
                        if (strcmp(word, keyword[i]) == 0)
                        {
                            strcat(function[place].function_stream, word);
                            k = 1;
                        }
                    }
                    if (k == 0 && c == '(')
                    {
                        strcat(function[place].function_stream, f2);
                    }
                    flag--;
                }
                flag++;
            }
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (strcmp(name[i], function[j].function_name) == 0 && function[j].n == 0)
            {
                strcat(mainstream[keepstream - 1].keystream, function[j].function_stream);
                function[j].n = 1;
            }
        }
    }
    /*for(int i=0;i<keepstream;i++) {
       printf("%d\n%s\n",mainstream[i].n,mainstream[i].keystream);
    }*/
    for (int i = 0; i < keepstream; i++)
    {
        int t = 0;
        for (int j = i + 1; j < keepstream; j++)
        {
            int editdistance;
            double sim;
            editdistance = editdistDP(mainstream[i].keystream, mainstream[j].keystream);
            sim = 1 - (double)editdistance / max2(strlen(mainstream[i].keystream), strlen(mainstream[j].keystream));
            if (sim >= 0.95)
            {
                if (t == 0)
                {
                    printf("%d %d", mainstream[i].n, mainstream[j].n);
                    t = 1;
                }
                else
                {
                    printf(" %d", mainstream[j].n);
                }
            }
        }
        if (t == 1)
        {
            printf("\n");
        }
    }
    return 0;
}
