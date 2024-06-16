#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct a
{
	char name[100];
	char xinxi[4096];
} hanshu;
typedef struct b
{
	int id;
	char xinxi[5000];
	// 函数信息
	hanshu func[300];
	// int fcount;
	// main函数顺序记录
	char main[300][300];
	int flag;
} chengxu;

chengxu B[1000];	// 程序结构数组
int top1 = 0;		// 计数程序数目
int fcount = 0;		// 函数个数
int top2 = 0;		// 计数函数信息流下标
int main_count = 0; // 计数main中函数出现顺序

char c;			 // 读入字符
char temp[1000]; // 读字符串时判断情况的临时数组
int top3 = 0;	 // 用于临时数组的计数

char test[5000][50]; // 检测表
int test_count = 0;	 // 记录检测表单词数量

FILE *in, *fp;
int istest(char s[])
{ // 判断是否在检测表中   /后期可优化，字典树，哈希，二分查找等
	int t;
	for (t = 0; t < test_count; t++)
	{
		if (strcmp(s, test[t]) == 0)
			return 1;
	}
	return 0;
}
void dealkong()
{
	char c;
	while (fscanf(in, "%c", &c) != EOF && (c == ' ' || c == '\n' || c == '\t' || c == '\r'))
	{
	}
	fseek(in, -1, SEEK_CUR); // ungetc(c,in)
}
/*
字符串编辑距离(Edit Distance)，是俄罗斯科学家Vladimir Levenshtein提出的概念。两个字符串之间的最小距离就是指把一个字符串转换为另一个字符串时，所需要的最小编辑操作(插入、删除、替换)的次数。
编辑操作包含以下3种：
替换（substitution），将一个字符替换为另一个字符
插入（insertion），插入一个字符
删除（deletion），删除一个字符
下面给出了一个基于动态规划算法的编辑距离计算函数editdistDP 的C语言实现，该函数参数为2个字符串，返回值为2个字符串的编辑距离，函数实现如下：
*/
#define max2(a, b) ((a) > (b) ? (a) : (b))
int **Dp, MaxDP = 3300; // for dynamic programming
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

int main()
{

	in = fopen("codes.txt", "r");
	fp = fopen("keepwords.txt", "r");
	int ismain = 0, left = 0, Left = 0, i, j, zhuangtai = 0, tt;
	while (fscanf(fp, "%s", test[test_count++]) != EOF)
	{ // 创建检测表
	}
	test_count--;

	while (fscanf(in, "%d", &B[top1++].id) != EOF)
	{ // 处理各个程序代码

		dealkong();
		while (fscanf(in, "%c", &c) != EOF && c != '\f')
		{ // 单个程序中处理
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
			{ // 处理函数名
				temp[top3++] = c;
				while (fscanf(in, "%c", &c) != EOF && c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != '(')
				{
					temp[top3++] = c;
				}
				if (c == '(')
					fseek(in, -1, SEEK_CUR);
				temp[top3] = '\0';
				top3 = 0;
				if (strcmp(temp, "main") == 0)
					ismain = 1;
				else
					ismain = 0;
				strcpy(B[top1 - 1].func[fcount++].name, temp);

				dealkong();
			}
			// 处理形参
			fscanf(in, "%c", &c);
			if (c == '(')
				left++;
			while (left > 0)
			{
				fscanf(in, "%c", &c);
				if (c == '(')
					left++;
				if (c == ')')
					left--;
			}
			dealkong();
			// 处理函数主体生成函数信息流
			fscanf(in, "%c", &c);
			if (c == '{')
			{
				Left++;
				B[top1 - 1].func[fcount - 1].xinxi[top2++] = c;
			}
			while (Left > 0)
			{
				c = fgetc(in);
				if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
				{
				}
				else if (((c >= 33 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 127)) && c != '_')
				{
					B[top1 - 1].func[fcount - 1].xinxi[top2++] = c;
					if (c == '(')
						left++;
					if (c == ')')
						left--;
					if (c == '{')
						Left++;
					if (c == '}')
						Left--;
				}
				else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
				{
					temp[top3++] = c;
					while (fscanf(in, "%c", &c) != EOF && ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_'))
					{
						temp[top3++] = c;
					}
					temp[top3] = '\0';
					fseek(in, -1, SEEK_CUR);
					if (istest(temp))
					{
						for (i = 0; i < top3; i++)
							B[top1 - 1].func[fcount - 1].xinxi[top2++] = temp[i];
					}
					else
					{
						dealkong();
						if (fscanf(in, "%c", &c) != EOF && c == '(')
						{
							fseek(in, -1, SEEK_CUR);
							if (ismain)
							{
								for (i = 0; i < main_count; i++)
								{
									if (strcmp(B[top1 - 1].main[i], temp) == 0)
									{
										zhuangtai = 1;
										break;
									}
								}
								if (zhuangtai == 0)
									strcpy(B[top1 - 1].main[main_count++], temp);
								zhuangtai = 0;
							}
							B[top1 - 1].func[fcount - 1].xinxi[top2++] = 'F';
							B[top1 - 1].func[fcount - 1].xinxi[top2++] = 'U';
							B[top1 - 1].func[fcount - 1].xinxi[top2++] = 'N';
							B[top1 - 1].func[fcount - 1].xinxi[top2++] = 'C';
						}
						else
						{
							ungetc(c, in);
						}
					}
					top3 = 0;
				}
			}
			top2 = 0;

			dealkong();
		}
		// 合并函数信息流生成程序信息流
		for (i = 0; i < fcount; i++)
		{
			if (strcmp(B[top1 - 1].func[i].name, "main") == 0)
			{
				strcpy(B[top1 - 1].xinxi, B[top1 - 1].func[i].xinxi);
				break;
			}
		}
		for (i = 0; i < main_count; i++)
		{
			for (j = 0; j < fcount; j++)
			{
				if (strcmp(B[top1 - 1].func[j].name, B[top1 - 1].main[i]) == 0)
				{
					strcat(B[top1 - 1].xinxi, B[top1 - 1].func[j].xinxi);
					break;
				}
			}
		}
		main_count = 0;
		fcount = 0;
	}
	// 进行距离相似度计算
	for (i = 0; i < top1; i++)
	{
		B[i].flag = 0;
	}
	int jishu = 0, distance, sim, y;
	int a[300], top = 0;
	for (i = 0; i < top1; i++)
	{
		top = 0;
		if (B[i].flag == 0)
		{
			for (j = 0; j < top1; j++)
			{
				distance = editdistDP(B[i].xinxi, B[j].xinxi);
				sim = 1 - (double)distance / max2(strlen(B[i].xinxi), strlen(B[j].xinxi));
				if (sim > 0.95)
				{
					a[top++] = B[j].id;
					B[j].flag = 1;
				}
			}
			if (top > 1)
			{
				for (y = 0; y < top; y++)
				{
					printf("%d ", a[y]);
				}
				printf("\n");
			}
		}
	}
	fclose(in);
	fclose(fp);
	return 0;
}
