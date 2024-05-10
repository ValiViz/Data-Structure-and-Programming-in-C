/*
加密文件
【问题描述】有一种加密方法为：其使用一个字母串（可以含重复字母，字母个数不超过50）作为密钥。假定密钥单词串为feather，则先去掉密钥单词中的重复字母得到单词串feathr，然后再将字母表中的其它字母以反序追加到feathr的后面：

 f	 e	 a	 t	 h	 r	 z	 y	 x	 w	 v	 u	 s	 q	 p	 o	 n	 m	 l	 k	 j	 i	 g	 d	 c	 b 
加密字母的对应关系如下：

 a	 b	 c	 d	 e	 f	 g	 h	 i	 j	 k	 l	 m	 n	 o	 p	 q	 r	 s	 t	 u	 v	 w	 x	 y	 z
 f	 e	 a	 t	 h	 r	 z	 y	 x	 w	 v	 u	 s	 q	 p	 o	 n	 m	 l	 k	 j	 i	 g	 d	 c	 b
其中第一行为原始英文字母，第二行为对应加密字母。其它字符不进行加密。编写一个程序，用这种密码加密文件。假定要加密的文件名为encrypt.txt及加密后的文件名为output.txt，并假定输入文件中字母全为小写字母，并且输入密钥也全为小写字母。

【输入形式】从标准输入中输入密钥串，并从文件encrypt.txt中读入要加密的内容。
【输出形式】加密后结果输出到文件output.txt中。
【样例输入】
feather
和文件encrypt.txt中内容，例如被加密的文件encrypt.txt中内容为：
c language is wonderful.
【样例输出】加密后output.txt文件中内容为：
a ufqzjfzh xl gpqthmrju.
【样例说明】首先将给定的密钥单词去除重复字母，然后按照上面的加密对应表对encrypt.txt文件内容进行加密即可得到加密后的文件，其中只对英文字母进行加密对换，并且假设encrypt.txt中的英文字母全是小写字母。

【评分标准】该题要求对文件进行加密，共有5个测试点。提交程序名为encrypt.c
*/

#include <stdio.h>

char str[27];
int exist[27] = {};

int main()
{
    FILE *IN, *OUT;
    if ((IN = fopen("encrypt.txt", "r")) == NULL)
    {
       printf("Can&rsquo;t open in.txt!");
    }
    OUT = fopen("output.txt", "w");

    char c;
    char *p = str;
    while ((c = getchar()) != EOF)
    {
        if (c >= 'a' && c <= 'z')
        {
            if (exist[c - 'a']) continue;
            exist[c - 'a']++;
            *(p++) = c;
        }
    }
    for (c = 'z'; c >= 'a'; c--)
    {
        if (!exist[c - 'a']) *(p++) = c;
    }

    while ((c = fgetc(IN)) != EOF)
    {
        if (c >= 'a' && c <= 'z') fputc(str[c - 'a'], OUT);
        else fputc(c, OUT);
    }

    fclose(IN);
    fclose(OUT);

    return 0;
}