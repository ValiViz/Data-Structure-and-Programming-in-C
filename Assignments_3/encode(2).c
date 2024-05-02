#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct node
{
	char data;

	struct node *link;
} LNode, *LinkList;

LinkList creat(char *s)
{
	LinkList p, r, list = NULL;

	char t;

	int i;

	for (i = 0; i < 95; i++)
	{
		t = s[i];

		p = (LinkList)malloc(sizeof(LNode));

		p->data = t;

		p->link = list;

		if (list == NULL)
		{
			list = p;
		}

		else
		{
			r->link = p;
		}

		r = p;
	}

	return (list);
}

int main()
{
	FILE *fa, *fb;

	fa = fopen("in.txt", "r");

	fb = fopen("in_crpyt.txt", "w");

	char key[500] = {'\0'}, s[500] = {'\0'}, a[500] = {'\0'};

	gets(key);

	int num = strlen(key), k = 1;

	s[0] = key[0];

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (key[i] == key[j])
			{
				break;
			}

			if (j == i - 1)
			{
				s[k] = key[i];

				k++;
			}
		}
	}

	for (int i = 0; i < 95 - k; i++)
	{
		for (char c = 32; c <= 126; c++)
		{
			int tmp = 0;

			for (int l = 0; l < i + k; l++)
			{
				if (c == s[l])
				{
					break;
				}

				if (l == i + k - 1)
				{
					s[i + k] = c;

					tmp = 1;

					break;
				}
			}

			if (tmp == 1)
			{
				break;
			}
		}
	}

	LinkList list = creat(s);

	LinkList p = list, q, first = list;

	for (int j = 0; j < 94; j++)
	{
		if (p == list)
		{
			q = p;

			LinkList r = list;

			while (r->link != p)
			{
				r = r->link;
			}

			r->link = p->link;

			list = r->link;

			for (int i = 0; i < (int)(q->data); i++)
			{
				p = p->link;
			}

			a[(int)(q->data)] = p->data;
		}

		else
		{
			q = p;

			LinkList r = list;

			while (r->link != p)
			{
				r = r->link;
			}

			r->link = p->link;

			for (int i = 0; i < (int)(q->data); i++)
			{
				p = p->link;
			}

			a[(int)(q->data)] = p->data;
		}
	}

	a[(int)(list->data)] = first->data;

	char z = fgetc(fa);

	while (z != EOF)
	{
		if (z == '\n')
		{
			fprintf(fb, "\n");
		}
		else
			fputc(a[(int)z], fb);

		z = fgetc(fa);
	}

	fclose(fa);

	fclose(fb);

	return 0;
}
