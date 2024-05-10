/*
	字符串替换（新）
【问题描述】

编写程序将一个指定文件中某一字符串替换为另一个字符串。要求：（1）被替换字符串若有多个，均要被替换；（2）指定的被替换字符串，大小写无关。

【输入形式】

给定文件名为filein.txt。从控制台输入两行字符串（不含空格，行末尾都有回车换行符），分别表示被替换的字符串和替换字符串。

【输出形式】

将替换后的结果输出到文件fileout.txt中。

【样例输入】

从控制台输入两行字符串：

in

out

文件filein.txt的内容为：

#include <stdio.h>

void main()

{

    FILE * IN;

    if((IN=fopen("in.txt","r"))==NULL)

    {

       printf("Can&rsquo;t open in.txt!");

       return;

    }

    fclose(IN);

}

【样例输出】

文件fileout.txt的内容应为：

#outclude <stdio.h>

void maout()

{

    FILE * out;

    if((out=fopen("out.txt","r"))==NULL)

    {

       prouttf("Can&rsquo;t open out.txt!");

       return;

    }

    fclose(out);

}

【样例说明】

输入的被替换字符串为in，替换字符串为out，即将文件filein.txt中的所有in字符串（包括iN、In、IN字符串）全部替换为out字符串，并输出保存到文件fileout.txt中。

【评分标准】

该题要求得到替换后的文件内容，共有5个测试点。上传C语言文件名为replace.c。
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void str_replace(char *desk, int top, int len, char *to)
{
    char tmp[1000];
    strcpy(tmp, to);
    strcat(tmp, (desk + top + len));
    *(desk + top) = '\0';
    desk = strcat(desk, tmp);
    return;
}

int same(char a, char b)
{
    return tolower(a) == tolower(b);
}

int main()
{
    FILE *IN, *OUT;
    if((IN = fopen("filein.txt", "r")) == NULL)
    {
       printf("Can&rsquo;t open in.txt!");
    }
    OUT = fopen("fileout.txt", "w");

    char str[1000], from[1000], to[1000];
    gets(from);
    int from_len = strlen(from);
    gets(to);
    int to_len = strlen(to);

    char *top, *now;
    while(fgets(str, 1000, IN) != NULL)
    {
        int str_len = strlen(str);
        now = str;
        for(int i = 0; i < str_len; i++)
        {
            int j;
            for(j = 0; j < from_len && same(str[i + j], from[j]); j++);
            if(j == from_len)
            {
                str_replace(str, i, from_len, to);
                i += to_len;
            }
            
        }
        fputs(str, OUT);
    }

    fclose(IN);
    fclose(OUT);

    return 0;
}