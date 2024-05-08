// �ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{ // Huffman���ṹ
	char c;
	int weight; // ���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left, *right;
};
int Ccount[128] = {0};			  // ���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ���
struct tnode *Root = NULL;		  // Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE] = {{0}}; // �ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ��
int Step = 0;					  // ʵ�鲽��
FILE *Src, *Obj;

void statCount();	// ����1��ͳ���ļ����ַ�Ƶ��
void createHTree(); // ����2������һ��Huffman�������ڵ�ΪRoot
void makeHCode();	// ����3������Huffman������Huffman����
void atoHZIP();		// ����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();				  // �������1�Ľ��
void print2(struct tnode *p); // �������2�Ľ��
void print3();				  // �������3�Ľ��
void print4();				  // �������4�Ľ��

int main()
{
	if ((Src = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if ((Obj = fopen("output.txt", "w")) == NULL)
	{
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d", &Step); // ���뵱ǰʵ�鲽��

	statCount(); // ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	if (Step == 1)
		print1();  // ���ʵ�鲽��1���
	createHTree(); // ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	if (Step == 2)
		print2(Root); // ���ʵ�鲽��2���
	makeHCode();	  // ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	if (Step == 3)
		print3(); // ���ʵ�鲽��3���
	if (Step >= 4)
		atoHZIP(), print4(); // ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���

	fclose(Src);
	fclose(Obj);

	return 0;
}

// ��ʵ�鲽��1����ʼ

void statCount()
{
	char c = 0;
	while ((c = fgetc(Src)) != EOF)
	{
		if (c == '\n')
			continue;
		Ccount[c]++;
	}
	Ccount[0] = 1;
}

// ��ʵ�鲽��1������

// ��ʵ�鲽��2����ʼ
int compar(const void *a, const void *b)
{
	struct tnode *A = *(struct tnode **)a, *B = *(struct tnode **)b;
	return A->weight == B->weight ? A->c - B->c : A->weight - B->weight;
}
void createHTree()
{
	struct tnode *F[1000];
	int size = 0;
	for (int i = 0; i < 128; i++)
		if (Ccount[i] > 0)
		{
			struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
			p->c = i;
			p->weight = Ccount[i];
			p->left = p->right = NULL;
			F[size++] = p;
		}
	qsort(F, size, sizeof(struct tnode *), compar);
	int bottom = 0;
	while (size - bottom > 1)
	{
		struct tnode *new = (struct tnode *)malloc(sizeof(struct tnode));
		new->left = F[bottom];
		new->right = F[bottom + 1];
		new->weight = F[bottom]->weight + F[bottom + 1]->weight;
		new->c = 0;
		F[++bottom] = new;
		int p = bottom;
		while (p + 1 < size && F[p]->weight >= F[p + 1]->weight)
		{
			struct tnode *tmp = F[p + 1];
			F[p + 1] = F[p];
			F[p] = tmp;
			p++;
		}
	}
	Root = F[bottom];
}

// ��ʵ�鲽��2������

// ��ʵ�鲽��3����ʼ
char str[100000] = "";
void Traverse(struct tnode *N, int depth)
{
	if (N == NULL)
		return;
	if (N->left == NULL && N->right == NULL)
	{
		strcpy(HCode[N->c], str);
		return;
	}
	else
	{
		strcat(str, "0");
		Traverse(N->left, depth + 1);
		str[depth] = '1';
		Traverse(N->right, depth + 1);
		str[depth] = '\0';
		return;
	}
}
void makeHCode()
{
	Traverse(Root, 0);
}

// ��ʵ�鲽��3������

// ��ʵ�鲽��4����ʼ

void atoHZIP()
{
	fseek(Src, 0, SEEK_SET);
	str[0] = '\0';
	char c;
	c = fgetc(Src);
	while (c != '\0')
	{
		strcat(str, HCode[c]);
		if ((c = fgetc(Src)) == EOF)
			c = '\0';
	}
	strcat(str, HCode[c]);
	unsigned char hc;
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{

		hc = (hc << 1) | (str[i] - '0');

		if ((i + 1) % 8 == 0)
		{

			fputc(hc, Obj); // �����Ŀ�꣨ѹ�����ļ���

			printf("%x", hc); // ��ʮ�������������Ļ��
		}
	}
	i %= 8;
	if (i)
	{
		hc = (hc << (8 - i));

		fputc(hc, Obj); // �����Ŀ�꣨ѹ�����ļ���

		printf("%x", hc); // ��ʮ�������������Ļ��
	}
}
// ��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for (i = 1; i < 128; i++)
		if (Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if (p != NULL)
	{
		if ((p->left == NULL) && (p->right == NULL))
			switch (p->c)
			{
			case 0:
				printf("NUL ");
				break;
			case ' ':
				printf("SP ");
				break;
			case '\t':
				printf("TAB ");
				break;
			case '\n':
				printf("CR ");
				break;
			default:
				printf("%c ", p->c);
				break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;

	for (i = 0; i < 128; i++)
	{
		if (HCode[i][0] != 0)
		{
			switch (i)
			{
			case 0:
				printf("NUL:");
				break;
			case ' ':
				printf("SP:");
				break;
			case '\t':
				printf("TAB:");
				break;
			case '\n':
				printf("CR:");
				break;
			default:
				printf("%c:", i);
				break;
			}
			printf("%s\n", HCode[i]);
		}
	}
}

void print4()
{
	long int in_size, out_size;

	fseek(Src, 0, SEEK_END);
	fseek(Obj, 0, SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);

	printf("\nyqjdx:%ldB\n", in_size);
	printf("yshwjdx:%ldB\n", out_size);
	printf("ysl:%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
