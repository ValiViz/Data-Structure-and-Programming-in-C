/*
通讯录整理
【问题描述】

读取一组电话号码簿（由姓名和手机号码组成），将重复出现的项删除（姓名和电话号码都相同的项为重复项，只保留第一次出现的项），并对姓名相同手机号码不同的项进行如下整理：首次出现的项不作处理，第一次重复的姓名后面加英文下划线字符_和数字1，第二次重复的姓名后面加英文下划线字符_和数字2，依次类推。号码簿中姓名相同的项数最多不超过10个。最后对整理后的电话号码簿按照姓名进行从小到大排序，并输出排序后的电话号码簿。

【输入形式】

先从标准输入读取电话号码个数，然后分行输入姓名和电话号码，姓名由不超过20个英文小写字母组成，电话号码由11位数字字符组成，姓名和电话号码之间以一个空格分隔，输入的姓名和电话号码项不超过100个。

【输出形式】

按照姓名从小到大的顺序分行输出最终的排序结果，先输出姓名再输出电话号码，以一个空格分隔。

【样例输入】

15

liping 13512345678

zhaohong 13838929457

qiansan 13900223399

zhouhao 18578294857

anhai 13573948758

liping 13512345678

zhaohong 13588339922

liping 13833220099

boliang 15033778877

zhaohong 13838922222

tianyang 18987283746

sunnan 13599882764

zhaohong 13099228475

liushifeng 13874763899

caibiao 13923567890

【样例输出】

anhai 13573948758

boliang 15033778877

caibiao 13923567890

liping 13512345678

liping_1 13833220099

liushifeng 13874763899

qiansan 13900223399

sunnan 13599882764

tianyang 18987283746

zhaohong 13838929457

zhaohong_1 13588339922

zhaohong_2 13838922222

zhaohong_3 13099228475

zhouhao 18578294857

【样例说明】

输入了15个人名和电话号码。其中第一项和第六项完全相同，都是“liping 13512345678”，将第六项删除，第一项保留；

第八项和第一项人名相同，电话不同，则将第八项的人名整理为liping_1；同样，第二项、第七项、第十项、第十三项的人名都相同，将后面三项的人名分别整理为：zhaohong_1、zhaohong_2和zhaohong_3。

最后将整理后的电话簿按照姓名进行从小到大排序，分行输出排序结果。

【评分标准】

该题要求编程实现通讯录的整理与排序，提交程序文件名为sort.c。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[20];
    char phone[20];
} PERSON;

int cmp(const void *a, const void *b)
{
    PERSON pa = *(PERSON*)a, pb = *(PERSON*)b;
    return strcmp(pa.name, pb.name);
}

int main()
{
    int count = 0;
    int N;
    scanf("%d", &N);
    PERSON list[105];
    PERSON now;
    while(N--)
    {
        scanf("%s%s", now.name, now.phone);
        int again = 0;
        for(int i = 0; i < count; i++)
        {
            if(strcmp(now.phone, list[i].phone) == 0)
            {
                goto QUIT;
            }
            if(strcmp(now.name, list[i].name) == 0)
            {
                if(!again)
                {
                    strcat(now.name, "_1");
                }
                else
                {
                    now.name[strlen(now.name) - 1] = '1' + again;
                }
                again++;
                continue;
            }
        }
        strcpy(list[count].name, now.name);
        strcpy(list[count].phone, now.phone);
        count++;
        QUIT:
        ;
    }

    qsort(list, count, sizeof(PERSON), cmp);

    for(int i = 0; i < count; i++)
    {
        printf("%s %s\n", list[i].name, list[i].phone);
    }

    return 0;
}