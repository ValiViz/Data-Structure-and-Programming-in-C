/*
	超长正整数的减法
【问题描述】
编写程序实现两个超长正整数（每个最长80位数字）的减法运算。
 
【输入形式】

从键盘读入两个整数，要考虑输入高位可能为0的情况（如00083）。
1. 第一行是超长正整数A；
2. 第二行是超长正整数B；
 
【输出形式】
输出只有一行，是长整数A减去长整数B的运算结果，从高到低依次输出各位数字。要求：若结果为0，则只输出一个0；否则输出的结果的最高位不能为0，并且各位数字紧密输出。
 【输入样例】
 
234098
134098703578230056
 
【输出样例】
 －134098703577995958

【样例说明】
进行两个正整数减法运算， 234098 －134098703578230056 = －134098703577995958。
 
【评分标准】
 完全正确得20分，每个测试点4分，提交程序文件名为subtract.c。
*/

#include <stdio.h>
#include <string.h>

char str[81], num1[81], num2[81], res[81] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000";

void work(char a[], char b[])
{
    for(int i = 80; i >= 0; i--)
    {
        if(a[i] >= b[i])
        {
            res[i] = a[i] - b[i] + '0';
        }
        else
        {
            a[i - 1]--;
            res[i] = a[i] + 10 - b[i] + '0';
        }
    }
    if(strcmp(res, "000000000000000000000000000000000000000000000000000000000000000000000000000000000") == 0)
    {
        puts("0");
        return;
    }
    int i;
    for(i = 0; i < 81 && res[i] == '0'; i++)
        ;
    puts(&res[i]);
    return;
}

int main()
{
    gets(str);
    int len1 = strlen(str);
    for(int i = 0; i < 81 - len1; i++)
    {
        strcpy(num1, res);
    }
    for(int i = 0; i < len1; i++)
    {
        strcpy(&num1[81 - len1], str);
    }

    gets(str);
    int len2 = strlen(str);
    for(int i = 0; i < 81 - len2; i++)
    {
        strcpy(num2, res);
    }
    for(int i = 0; i < len2; i++)
    {
        strcpy(&num2[81 - len2], str);
    }

    if(strcmp(num1, num2)<0)
    {
        printf("-");
        work(num2, num1);
    }
    else
    {
        work(num1, num2);
    }

    return 0;
}