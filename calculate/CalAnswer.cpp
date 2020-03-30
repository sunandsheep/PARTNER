#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>

using namespace std;

#define ERROR -1
#define TRUE  0

typedef int Status;
extern int title_num;


void JudgeNumber(int fenzi, int fenmu, char s[]);
int Sequence(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope);

Status CalAnswer(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, char ans[])
{
	int sum, i, m, t[2], f[8];	//t[0]分子，t[1]分母

	for (i = 0; i < 8; i++)
	{
		f[i] = figure[i];
	}

	sum = Sequence(figure, operate, type_fig, num_fig, num_ope, tag_ope);
	m = pow(10, num_ope - 1);
	while (m)
	{
		i = sum / m - 1;

		if (operate[i] == '+')
		{
			t[0] = f[i] * f[i + 5] + f[i + 1] * f[i + 4];
			t[1] = f[i + 4] * f[i + 5];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		if (operate[i] == '-')
		{
			t[0] = f[i] * f[i + 5] - f[i + 1] * f[i + 4];
			if (t[0] < 0) return ERROR;		//判断是否出现负数
			t[1] = f[i + 4] * f[i + 5];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		if (operate[i] == '*')
		{
			t[0] = f[i] * f[i + 4];
			t[1] = f[i + 1] * f[i + 5];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		if (operate[i] == '/')
		{
			if (f[i + 1] == 0) return ERROR;		//防止被除数为0
			t[0] = f[i] * f[i + 5];
			t[1] = f[i + 1] * f[i + 4];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}

		sum = sum % m;
		m /= 10;
	}
	JudgeNumber(t[0], t[1], ans);

	return TRUE;
}

int Sequence(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope)
{
	int sum = 0, j;
	if (tag_ope > 10)
	{
		sum = Sequence(figure, operate, type_fig, num_fig, tag_ope % 10 - 1, tag_ope - (tag_ope % 10));
	}

	for (j = tag_ope / 10 - 1; j < num_ope; j++)
	{
		if (operate[j] == '*' && j + 1 != sum % 10 && j + 1 != sum / 10)
		{
			sum = sum * 10 + j + 1;
		}
		else if (operate[j] == '/' && j + 1 != sum % 10 && j + 1 != sum / 10)
		{
			sum = sum * 10 + j + 1;
		}
	}
	for (j = tag_ope / 10 - 1; j < num_ope; j++)
	{
		if (operate[j] == '+' && j + 1 != sum % 10 && j + 1 != sum / 10)
		{
			sum = sum * 10 + j + 1;
		}
		else if (operate[j] == '-' && j + 1 != sum % 10 && j + 1 != sum / 10)
		{
			sum = sum * 10 + j + 1;
		}
	}

	return sum;
}

