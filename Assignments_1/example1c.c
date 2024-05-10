/*
表达式计算（支持空格，连乘，连除）
【问题描述】

从标准输入中读入一个整数算术运算表达式，如5 - 1 * 2 * 3 + 12 / 2 / 2  = 。计算表达式结果，并输出。

要求：
1、表达式运算符只有+、-、*、/，表达式末尾的’=’字符表示表达式输入结束，表达式中可能会出现空格；
2、表达式中不含圆括号，不会出现错误的表达式；
3、出现除号/时，以整数相除进行运算，结果仍为整数，例如：5/3结果应为1。

【输入形式】

在控制台中输入一个以’=’结尾的整数算术运算表达式。

【输出形式】

向控制台输出计算结果（为整数）。

【样例1输入】

5 - 1 * 2 * 3 + 12 / 2 / 2  =

【样例1输出】

2

【样例2输入】

500 =

【样例2输出】

500

【样例1说明】

输入的表达式为5 - 1 * 2 * 3 + 12 / 2 / 2 =，按照整数运算规则，计算结果为2，故输出2。

【样例2说明】

输入的表达式为500 = ，没有运算符参与运算，故直接输出500。

算法之一提示：
1、可以利用gets函数，读取整行表达式；
2、对于空格，可以考虑首先去除表达式中的所有空格
3、可以设一计数器用来记录已读取、但未参加运算的运算符的个数，根据该计数器来判断如何进行运算；
4、可以设计一函数：实现二元整数算术运算。

【评分标准】

该题要求输出整数表达式的计算结果，共有5个测试点。上传C语言文件名为example1c.c。

 
*/

#include <stdio.h>
#define SPACE_ASKII 32
#define POSITIVE_SIGN 1

char scanf_without_space(char *site)
{
    do
    {
        scanf("%c", site);
    } while (*site == SPACE_ASKII);
    
}

int cal(int top_num, char now_cal_sign, int sign)
{
    int next_num;
    char next_cal_sign;
    switch (now_cal_sign)
    {
    case '*':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        top_num *= next_num;
        return cal(top_num, next_cal_sign, sign);
    case '/':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        top_num /= next_num;
        return cal(top_num, next_cal_sign, sign);
    case '+':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        return top_num + sign * cal(next_num, next_cal_sign, 1);
    case '-':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        return top_num - sign * cal(next_num, next_cal_sign, -1);
    case '=':
        return top_num;
    default:
        return EOF;
    }
}

int main()
{
    int top_num;
    char now_cal_sign;
    scanf("%d", &top_num);
    scanf_without_space(&now_cal_sign);
    int result = cal(top_num, now_cal_sign, POSITIVE_SIGN);
    printf("%d\n", result);

    return 0;
}