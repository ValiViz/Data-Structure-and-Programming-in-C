/*
扩展字符A
【问题描述】
从键盘输入包含扩展符'-'的字符串，将其扩展为等价的完整字符，例如将a-d扩展为abcd，并输出扩展后的字符串。

要求：只处理[a-z]、[A-Z]、[0-9]范围内的字符扩展，即只有当扩展符前后的字符同时是小写字母、大写字母或数字，并且扩展符后的字符大于扩展符前的字符时才进行扩展，其它情况不进行扩展，原样输出。例如：a-R、D-e、0-b、4-B等字符串都不进行扩展。


【输入形式】
从键盘输入包含扩展符的字符串
【输出形式】
输出扩展后的字符串

【输入样例1】
ADEa-g-m02
【输出样例1】
ADEabcdefghijklm02

【输入样例2】
cdeT-bcd
【输出样例2】
cdeT-bcd

【样例说明】
将样例1的输入ADEa-g-m02扩展为：ADEabcdefghijklm02；样例2的输入cdeT-bcd中，扩展符前的字符为大写字母，扩展符后的字符为小写字母，不在同一范围内，所以不进行扩展。
【评分标准】
该题要求扩展字符，提交程序文件expand.c。
*/

#include <stdio.h>
#include <stdlib.h>

int sort(char c)
{
    if(c>='a'&&c<='z') return 1;
    if(c>='A'&&c<='Z') return 2;
    if(c>='0'&&c<='9') return 3;
    return 0;
}

int main()
{
    char last, now, next;
    last=getchar();
    printf("%c", last);
    while((now = getchar()) != EOF)
    {
        if(now!='-')
        {
            printf("%c", now);
            last = now;
        }
        else
        {
            if((next = getchar()) !=EOF)
            {
                if(sort(last)&&sort(last)==sort(next)&&next>last)
                {
                    for(char ch = last + 1; ch <= next; ch++)
                    {
                        printf("%c", ch);
                    }
                    last = next;
                }
                else
                {
                    printf("-%c", next);
                }
            }
            else
            {
                printf("-");
            }
        }
    }

    return 0;
}