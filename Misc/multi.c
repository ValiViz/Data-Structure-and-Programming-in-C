#include <stdio.h>
#include <malloc.h>

struct num
{
	int a, b;
};

typedef struct node
{
	struct num data;

	struct node *link;
} LNode, *LinkList;

LinkList creat1()
{
	LinkList p, r, list = NULL;

	struct num t;

	int i;

	char c;

	do
	{
		scanf("%d%d%c", &t.a, &t.b, &c);

		p = (LinkList)malloc(sizeof(LNode));

		p->data = t;

		p->link = NULL;

		if (list == NULL)
		{
			list = p;
		}

		else
		{
			r->link = p;
		}

		r = p;

	} while (c != 10);

	return (list);
}

LinkList creat2()
{
	LinkList p, r, list = NULL;

	struct num t;

	int i;

	while (scanf("%d%d", &t.a, &t.b) != EOF)
	{
		p = (LinkList)malloc(sizeof(LNode));

		p->data = t;

		p->link = NULL;

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
	LinkList list1 = creat1(),
			 list2 = creat2(),
			 list3 = NULL, r, p = list1, q = list2;

	r = list3;

	while (p != NULL)
	{
		while (q != NULL)
		{
			struct num tem;

			tem.a = p->data.a * q->data.a;

			tem.b = p->data.b + q->data.b;

			LinkList p1, q1, r1;

			p1 = (LinkList)malloc(sizeof(LNode));

			p1->data = tem;

			if (list3 == NULL || tem.b > list3->data.b)
			{
				p1->link = list3;

				list3 = p1;
			}

			else
			{
				int e = 0;

				q1 = list3;

				while (q1 != NULL && tem.b < q1->data.b)
				{
					r1 = q1;

					q1 = q1->link;

					if (q1 != NULL && tem.b == q1->data.b)
					{
						q1->data.a += tem.a;

						e = 1;

						break;
					}
				}

				if (e == 0)
				{
					p1->link = q1;

					r1->link = p1;

					if (q1 == NULL)
					{
						r = p1;
					}
				}
			}

			q = q->link;
		}

		q = list2;

		p = p->link;
	}

	LinkList z = list3;

	while (z != NULL)
	{
		printf("%d %d ", z->data.a, z->data.b);

		z = z->link;
	}

	return 0;
}
