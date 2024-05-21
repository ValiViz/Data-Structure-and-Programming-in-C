#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 开大了疑似过不了编译
#define MAXSIZE 200
#define MAXNAMELENGTH 100
#define MAXLENGTH 4096

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define max2(a, b) ((a) > (b) ? (a) : (b))
#define MAXSIMRATE 0.95
typedef int Status;
char keepwords[165][10] = {"abort", "abs", "acos", "asctime", "asin", "assert", "atan", "atan2", "atexit", "atof", "atoi", "atol", "auto", "break", "bsearch", "calloc", "case", "ceil", "char", "clearerr", "clock", "const", "continue", "cos", "cosh", "ctime", "default", "difftime", "div", "do", "double", "else", "enum", "exit", "exp", "extern", "fabs", "fclose", "feof", "ferror", "fflush", "fgetc", "fgetpos", "fgets", "float", "floor", "fmod", "fopen", "for", "fprintf", "fputc", "fputs", "fread", "free", "freopen", "frexp", "fscanf", "fseek", "fsetpos", "ftell", "fwrite", "getc", "getchar", "getenv", "gets", "gmtime", "goto", "if", "int", "isalnum", "isalpha", "iscntrl", "isdigit", "isgraph", "islower", "isprint", "ispunct", "isspace", "isupper", "isxdigit", "labs", "ldexp", "ldiv", "localtime", "log", "log10", "long", "longjmp", "malloc", "memchr", "memcmp", "memcpy", "memmove", "memset", "mktime", "modf", "perror", "pow", "printf", "putc", "putchar", "puts", "qsort", "raise", "rand", "realloc", "register", "remove", "rename", "return", "rewind", "scanf", "setbuf", "setjmp", "setvbuf", "short", "signal", "signed", "sin", "sinh", "sizeof", "sprintf", "sqrt", "srand", "sscanf", "static", "strapn", "strcapn", "strcat", "strchr", "strcmp", "strcpy", "strerror", "strftime", "strlen", "strncat", "strncmp", "strncpy", "strpbrk", "strrchr", "strstr", "strtod", "strtok", "strtol", "strtoul", "struct", "switch", "system", "tan", "tanh", "time", "tmpfile", "tmpnam", "tolower", "toupper", "typedef", "ungetc", "union", "unsigned", "va_arg", "va_end", "va_start", "void", "volatile", "while"};

// 基于首字母打表的快速搜索
int search_from[26] = {0, 13, 15, 26, 31, 36, 61, 67, 67, 80, 80, 80, 88, 96, 96, 96, 102, 103, 111, 148, 156, 159, 164, 165, 165, 165};

typedef struct function
{
    // 函数名
    char name[MAXNAMELENGTH];
    // char information_flow[MAXLENGTH];
    // 函数关键信息流
    char key_information_flow[MAXLENGTH];
    // 函数是否被调用
    Status is_called;
} function;

typedef struct program
{
    // 程序编号
    int number;
    // 程序main函数信息流
    char main_information_flow[MAXLENGTH];
    // 程序用户定义函数数
    int functions_size;
    // 程序用户定义函数
    function functions[MAXSIZE];
    // 程序关键信息流
    char key_information_flow[MAXLENGTH];
    // 程序被调用的用户定义函数数
    int called_functions_size;
    // 程序被调用的用户定义函数（以main调用序）
    function *called_functions[MAXSIZE];
    // 程序是否被查出相似过
    int is_sim;
} program;

Status init_program(program *P)
{
    P->functions_size = 0;
    P->called_functions_size = 0;
    P->is_sim = FALSE;
    return OK;
}

Status init_function(function *F)
{
    F->key_information_flow[0] = '\0';
    F->is_called = FALSE;
    F->name[0] = '\0';
    return OK;
}

// str[0]开始的标识符长度，若不是标识符返回0
int sign_word_length(char *str)
{
    char c = *str;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
    {
        char *p = str + 1;

        // 将( ) [ ] { } " ' : ; . * + - = ! & \n \r \t 跳过
        while (*p != ' ' && *p != '\0' && *p != '(' && *p != ')' && *p != '{' && *p != '}' && *p != '[' && *p != ']' && *p != '!' && *p != '=' && *p != '>' && *p != '<' && *p != '\"' && *p != '\'' && *p != ':' && *p != ';' && *p != '.' && *p != '*' && *p != '+' && *p != '-' && *p != '&' && *p != '|' && *p != ',' && *p != '\n' && *p != '\r')
        {
            p++;
        }
        return p - str;
    }
    return 0;
}

// 二分查找keepwords
Status search_between(int a, int b, char *str)
{
    if (a + 1 == b || a == b)
    {
        return strcmp(str, keepwords[a]) == 0;
    }
    int p = (a + b) / 2;
    int ans = strcmp(str, keepwords[p]);
    if (ans == 0)
        return TRUE;
    if (ans > 0)
        return search_between(p, b, str);
    else
        return search_between(a, p, str);
}

// 判断是否是keepwords
Status is_keepwords(char *str)
{
    if (str[0] < 'a' || str[0] > 'w')
        return FALSE;
    int a = search_from[str[0] - 'a'], b = search_from[str[0] - 'a' + 1];
    return search_between(a, b, str);
}

int number_16_length(char *str)
{
    char *p = str + 2;
    while ((*p <= '9' && *p >= '0') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F'))
    {
        p++;
    }
    return p - str;
}

int strcat_cur(int cur, char *desk, char *src)
{
    char *p = src, *q = desk + cur;
    for (; *p != '\0'; p++, q++)
    {
        *q = *p;
    }
    *q = *p;
    return q - desk;
}

Status scan_program(FILE *fp, program *code)
{
    if (feof(fp))
        return ERROR;
    init_program(code);
    if (fscanf(fp, "%d", &code->number) == EOF)
        return ERROR;
    char str[MAXNAMELENGTH];

    // 循环：FUNC(){}
    while (!feof(fp))
    {
        char c = '\f';
        // 读入回车符
        while ((c = fgetc(fp)) != EOF)
        {
            if (c == '\n' || c == '\r')
            {
                continue;
            }
            else if (c == '\f')
            {
                break;
            }
            else
            {
                fseek(fp, -1, SEEK_CUR);
                break;
            }
        }
        if (c == '\f')
        {
            break;
        }
        int small_flag = 0, big_flag = 0;
        Status is_main = FALSE;
        Status big_complete = FALSE;
        int cur = 0;
        Status get_name = TRUE;
        init_function(&code->functions[code->functions_size]);
        Status func_flag = FALSE;

        // 循环：string
        while (small_flag || big_flag || !big_complete)
        {
            if (fscanf(fp, "%s", str) == EOF)
                return ERROR;
            char sign_word[MAXNAMELENGTH];
            char *p = str;

            // 循环：char
            do
            {
                // if (feof(fp))
                //     return ERROR;
                char name[MAXNAMELENGTH];
                if (get_name)
                {
                    get_name = FALSE;
                    for (; *p != '\0' && *p != '('; p++)
                    {
                        name[p - str] = *p;
                    }
                    name[p - str] = '\0';
                    if (strcmp(name, "main") == 0)
                    {
                        is_main = TRUE;
                    }
                    else
                    {
                        strcpy(code->functions[code->functions_size].name, name);
                    }
                    char c = '(';
                    fseek(fp, -strlen(str) + strlen(name), SEEK_CUR);
                    do
                    {
                        c = fgetc(fp);
                    } while (c != '{');
                    fseek(fp, -1, SEEK_CUR);
                    if (fscanf(fp, "%s", str) == EOF)
                        return ERROR;
                    p = str;
                }
                if (is_main)
                {
                    // 填补程序main函数信息流
                    for (; *p != '\0'; p++)
                    {
                        if (*p == '(')
                        {
                            small_flag++;
                        }
                        else if (*p == ')')
                        {
                            small_flag--;
                        }
                        else if (*p == '{')
                        {
                            big_flag++;
                        }
                        else if (*p == '}')
                        {
                            big_flag--;
                            big_complete = TRUE;
                        }
                        code->main_information_flow[cur] = *p;
                        cur++;
                    }
                    code->main_information_flow[cur++] = ' ';
                    code->main_information_flow[cur] = '\0';
                    // puts(code->main_information_flow);
                }
                else
                {
                    // 填补函数关键信息流
                    for (; *p != '\0';)
                    {
                        if (*p == '(')
                        {
                            small_flag++;
                            p++;
                            if (func_flag)
                            {
                                if (is_keepwords(&sign_word[0]))
                                {
                                    cur = strcat_cur(cur, code->functions[code->functions_size].key_information_flow, sign_word);
                                }
                                else
                                {
                                    code->functions[code->functions_size].key_information_flow[cur++] = 'F';
                                    code->functions[code->functions_size].key_information_flow[cur++] = 'U';
                                    code->functions[code->functions_size].key_information_flow[cur++] = 'N';
                                    code->functions[code->functions_size].key_information_flow[cur++] = 'C';
                                    code->functions[code->functions_size].key_information_flow[cur] = '\0';
                                }
                                func_flag = FALSE;
                            }
                            code->functions[code->functions_size].key_information_flow[cur++] = '(';
                            code->functions[code->functions_size].key_information_flow[cur] = '\0';
                            continue;
                        }
                        else if (func_flag)
                        {
                            if (is_keepwords(sign_word))
                            {
                                cur = strcat_cur(cur, code->functions[code->functions_size].key_information_flow, sign_word);
                            }
                            func_flag = FALSE;
                        }
                        if (*p == ')')
                        {
                            small_flag--;
                            p++;
                            code->functions[code->functions_size].key_information_flow[cur++] = ')';
                            code->functions[code->functions_size].key_information_flow[cur] = '\0';
                        }
                        else if (*p == '{')
                        {
                            big_flag++;
                            p++;
                            code->functions[code->functions_size].key_information_flow[cur++] = '{';
                            code->functions[code->functions_size].key_information_flow[cur] = '\0';
                        }
                        else if (*p == '}')
                        {
                            big_flag--;
                            p++;
                            code->functions[code->functions_size].key_information_flow[cur++] = '}';
                            code->functions[code->functions_size].key_information_flow[cur] = '\0';
                            big_complete = TRUE;
                        }
                        else
                        {
                            int length = sign_word_length(p);
                            if (length)
                            {
                                int i = 0;
                                for (; i < length; i++)
                                {
                                    sign_word[i] = *p;
                                    p++;
                                }
                                sign_word[i] = '\0';
                                func_flag = TRUE;
                            }
                            else if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X'))
                            {
                                int length = number_16_length(p);
                                int i = 0;
                                for (; i < length; i++)
                                {
                                    sign_word[i] = *p;
                                    p++;
                                }
                                sign_word[i] = '\0';
                                cur = strcat_cur(cur, code->functions[code->functions_size].key_information_flow, sign_word);
                            }
                            else
                            {
                                code->functions[code->functions_size].key_information_flow[cur++] = *p;
                                code->functions[code->functions_size].key_information_flow[cur] = '\0';
                                p++;
                            }
                        }
                    }
                    // puts(code->functions[code->functions_size].key_information_flow);
                }
            } while (*p != '\0');
        }
        if (!is_main)
        {
            // puts(code->functions[code->functions_size].name);
            // puts(code->functions[code->functions_size].key_information_flow);
            code->functions_size++;
        }
        else
        {
            // puts("main");
            // puts(code->main_information_flow);
        }
    }
    return OK;
}

Status generate_program_key_information_flow(program *P)
{
    char sign_word[MAXNAMELENGTH];
    Status func_flag = FALSE;
    Status get_name = TRUE;
    Status is_main = FALSE;
    int cur = 0;
    for (char *p = P->main_information_flow; *p != '\0';)
    {
        while (*p == ' ')
        {
            p++;
        }
        if (*p == '\0')
            break;
        if (*p == '(')
        {
            p++;
            if (func_flag)
            {
                if (is_keepwords(sign_word))
                {
                    cur = strcat_cur(cur, P->key_information_flow, sign_word);
                }
                else
                {
                    int i = 0;
                    for (; i < P->functions_size; i++)
                    {
                        if (strcmp(sign_word, P->functions[i].name) == 0)
                        {
                            if (!P->functions[i].is_called)
                            {
                                P->functions[i].is_called = TRUE;
                                P->called_functions[P->called_functions_size] = &P->functions[i];
                                P->called_functions_size++;
                            }
                            break;
                        }
                    }
                    if (i < P->functions_size)
                        cur = strcat_cur(cur, P->key_information_flow, "FUNC");
                }
                func_flag = FALSE;
            }
            P->key_information_flow[cur++] = '(';
            P->key_information_flow[cur] = '\0';
            continue;
        }
        else if (func_flag)
        {
            if (is_keepwords(sign_word))
            {
                cur = strcat_cur(cur, P->key_information_flow, sign_word);
            }
            func_flag = FALSE;
        }
        while (*p == ' ')
        {
            p++;
        }
        if (*p == ')')
        {
            p++;
            P->key_information_flow[cur++] = ')';
            P->key_information_flow[cur] = '\0';
        }
        else if (*p == '{')
        {
            p++;
            P->key_information_flow[cur++] = '{';
            P->key_information_flow[cur] = '\0';
        }
        else if (*p == '}')
        {
            p++;
            P->key_information_flow[cur++] = '}';
            P->key_information_flow[cur] = '\0';
        }
        else
        {
            int length = sign_word_length(p);
            if (length)
            {
                int i = 0;
                for (; i < length; i++)
                {
                    sign_word[i] = *p;
                    p++;
                }
                sign_word[i] = '\0';
                func_flag = TRUE;
            }
            else
            {
                if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X'))
                {
                    int length = number_16_length(p);
                    int i = 0;
                    for (; i < length; i++)
                    {
                        sign_word[i] = *p;
                        p++;
                    }
                    sign_word[i] = '\0';
                    strcat(P->key_information_flow, sign_word);
                }
                else
                {
                    char str[2] = {*p, '\0'};
                    strcat(P->key_information_flow, str);
                    p++;
                }
            }
        }
    }
    for (int i = 0; i < P->called_functions_size; i++)
    {
        strcat(P->key_information_flow, P->called_functions[i]->key_information_flow);
    }
    return OK;
}

// Status is_called(program *P, function *F)
// {
//     if (is_keepwords(F->name))
//         return FALSE;
//     int length = strlen(F->name);
//     char *p = strstr(F->name, P->main_information_flow);
// }

// 计算相似度
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
double sim(program *P1, program *P2)
{
    char *str1 = P1->key_information_flow, *str2 = P2->key_information_flow;
    int i, j;
    int len1, len2;
    static int flag = 0;
    (flag++) ? 1 : initDP();
    len1 = strlen(str1) + 1;
    len2 = strlen(str2) + 1;
    (max2(len1, len2) >= MaxDP) ? error2("DP memory error!") : len1;
    if (str1[3] == str2[3] && str1[5] == str2[5] && str1[7] == str2[7] && str1[9] == str2[9])
    {
        if (strcmp(str1, str2) == 0)
        {
            return 1;
        }
    }

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
    double ans = 1 - (double)Dp[len1][len2] / max2(len1 - 1, len2 - 1);
    return ans;
}

program codes[MAXSIZE];
int main()
{
    FILE *IN = fopen("codes.txt", "r");

    // debug用
    FILE *OUT = fopen("test.txt", "w");

    // 读入待查重的代码，随之生成函数关键信息流或生成main函数信息流
    int codes_size = 0;
    while (scan_program(IN, &codes[codes_size]))
    {
        codes_size++;
    }

    // 生成程序关键信息流
    for (int i = 0; i < codes_size; i++)
    {
        if (!generate_program_key_information_flow(&codes[i]))
            return -1;

        // debug用
        // fprintf(OUT, "%d程序关键信息流\n", codes[i].number);
        fputs(codes[i].key_information_flow, OUT);
        fputc('\n', OUT);
        // fputs("------------------------------------------------------------------------------------------", OUT);
        // fputc('\n', OUT);
    }

    // 计算相似度并输出相似代码
    int is_sim[MAXSIZE][MAXSIZE] = {0};
    for (int i = 0; i < codes_size; i++)
    {
        if (codes[i].is_sim)
            continue;
        // codes[i].is_sim = TRUE;
        Status is_sim_code_existing = FALSE;
        program *sim_program[MAXSIZE] = {};
        int sim_program_size = 0;
        for (int j = 0; j < codes_size; j++)
        {
            if (j == i)
            {
                sim_program[sim_program_size] = &codes[j];
                sim_program_size++;
                continue;
            }
            if (is_sim[i][j] == 0)
            {
                is_sim[i][j] = (sim(&codes[i], &codes[j]) > MAXSIMRATE ? 1 : -1);
                is_sim[j][i] = is_sim[i][j];
            }

            // printf("%d %d %lf\n", codes[i].number, codes[j].number, tmp_sim);
            if (is_sim[i][j] == 1)
            {
                if (!is_sim_code_existing)
                {
                    // printf("%d", codes[i].number);
                    is_sim_code_existing = TRUE;
                }
                sim_program[sim_program_size] = &codes[j];
                sim_program_size++;
                codes[j].is_sim = TRUE;
            }
        }
        if (is_sim_code_existing)
        {
            for (int i = 0; i < sim_program_size; i++)
            {
                printf("%d ", sim_program[i]->number);
            }
            printf("\n");
        }
    }
    return 0;
}