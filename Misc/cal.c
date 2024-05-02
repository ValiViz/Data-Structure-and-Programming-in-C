#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
enum oper
{
	ept,
	add,
	min,
	mul,
	dive,
	left,
	right
};									// ö����
int pri[] = {-1, 0, 0, 1, 1, 2, 2}; // ��Ӧenum oper���ȼ�
enum symbol
{
	num,
	op,
	eq,
	other
}; // ����
union sym
{
	int num;
	enum oper fuhao;
}; // ���������������
int a[100], ntop = -1, otop = -1;
enum oper b[100];
enum symbol getsym(union sym *item)
{
	int c, n;
	while ((c = getchar()) != '=')
	{
		if (c == ' ')
			c = getchar();
		if (c >= '0' && c <= '9')
		{
			for (n = 0; c > '0' && c < '9'; c = getchar())
				n = n * 10 + c - '0';
			ungetc(c, stdin); // �˻��ַ�
			item->num = n;
			return num;
		}
		else
		{
			switch (c)
			{
			case '+':
				item->fuhao = add;
				return op;
			case '-':
				item->fuhao = min;
				return op;
			case '*':
				item->fuhao = mul;
				return op;
			case '/':
				item->fuhao = dive;
				return op;
			case '(':
				item->fuhao = left;
				return op;
			case ')':
				item->fuhao = right;
				return op;
			}
		}
	}
};
void operate(enum oper op);
// {
// 	if(op==right){
// 		while(topop()!=left){
// 			compute(popop());
// 		}
// 	}
// 	else{
// 		while(pri[topop()]>pri[op]){
// 			compute(popop());
// 		}
// 		pushop(op);
// 	}
// };
void compute(enum oper op);
// {
// 	int t;
// 	switch (op)
// 	{
// 	case add:
// 		pushnum(popnum() + popnum());
// 		return;
// 	case min:
// 		t = popnum();
// 		push(popnum() - t);
// 		return;
// 	case mul:
// 		push(popnum() * popnum());
// 		return;
// 	case dive:
// 		t = popnum();
// 		push(popnum() / t);
// 		return;
// 	}
// };
void pushnum(int item)
{
	a[++ntop] = num;
};
int popnum()
{
	return a[ntop--];
};
void pushop(enum oper op)
{
	b[++otop] == op;
};
enum oper popop()
{
	if (otop != -1)
		return b[otop--];
	return ept;
};
enum oper topop()
{
	return b[otop];
};
int main()
{
	union sym item;
	enum symbol s;
	while ((s = getsym(&item)) != eq)
	{
		if (s == num)
		{
			pushnum(item.num);
		}
		else if (s == op)
		{
			operate(item.fuhao);
		}
	}
	while (otop >= 0)
		compute(popop());
	printf("%d\n", popnum());
	return 0;
}
void operate(enum oper op)
{
	if (op == right)
	{
		while (topop() != left)
		{
			compute(popop());
		}
	}
	else
	{
		while (pri[topop()] > pri[op])
		{
			compute(popop());
		}
		pushop(op);
	}
};
void compute(enum oper op)
{
	int t;
	switch (op)
	{
	case add:
		pushnum(popnum() + popnum());
		return;
	case min:
		t = popnum();
		pushnum(popnum() - t);
		return;
	case mul:
		pushnum(popnum() * popnum());
		return;
	case dive:
		t = popnum();
		pushnum(popnum() / t);
		return;
	}
};