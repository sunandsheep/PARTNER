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
int title_num;
int answer[10000];
int seq[10000];
int Figure[10000][8];


void CreatQuestions(int number, int range);	//创建题目
void JudgeNumber(int ans[]);		//判断真分数是否需要化简
void JudgeRepeat();				//判断题目是否重复
Status CalAnswer(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, int ans[]);		//计算答案
void WriteFile(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file);  //题目放入文件
void WriteAnswer(int ans[], FILE* file);		//答案放入文件
int Sequence(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope); //计算顺序
int gcd(int x, int y);		//求最大公因数

int main()
{
	int number;
	printf("请输入题目个数\n");
	scanf("%d", &number);

	int range;
	printf("请输入数值范围\n");
	scanf("%d", &range);

	CreatQuestions(number, range);

	return 0;
}

//创建题目
void CreatQuestions(int number, int range)
{
	int num_ope, type_ope, num_fig, type_fig, t;
	int figure[8], ans[3];
	char operate[3];

	srand(time(NULL));
	title_num = 0;

	FILE* question_file;
	FILE* answer_file;
	if ((question_file = fopen("Exercise.txt", "a+")) == NULL)
	{
		printf("You can't open the file!\n");
		exit(1);
	}
	if ((answer_file = fopen("Answers.txt", "a+")) == NULL)
	{
		printf("You can't open the file!\n");
		exit(1);
	}

	while (number != title_num)
	{
		int i, rand1, tag_ope = 10;
		num_ope = (rand() % 3) + 1;
		num_fig = num_ope + 1;
		figure[4] = figure[5] = figure[6] = figure[7] = 1;
		ans[0] = ans[1] = 0;   ans[2] = 1;

		//确定数字
		for (i = 0; i < num_fig; i++)
		{
			figure[i] = rand() % range;
			type_fig = rand() % 2;		//0自然数，1真分数
			if (type_fig == 1 && figure[i] != 0)
			{
				figure[i + 4] = rand() % range;
				while (figure[i + 4] == 0 || figure[i] % figure[i + 4] == 0)
				{
					figure[i + 4] = rand() % range;
				}
				t = gcd(figure[i], figure[i + 4]);
				figure[i] = figure[i] / t;
				figure[i + 4] = figure[i + 4] / t;
			}
		}

		//确定符号
		for (i = 0; i < num_ope; i++)
		{
			rand1 = rand() % 4 + 1;
			switch (rand1)
			{
			case 1: operate[i] = '+'; break;
			case 2: operate[i] = '-'; break;
			case 3: operate[i] = '*'; break;
			case 4: operate[i] = '/'; break;
			default:break;
			}
		}

		//确定是否有括号及括号位置
		if (num_fig == 3)
		{
			rand1 = (rand() % 3 + 1) + (rand() % 3 + 1) * 10;
			switch (rand1)
			{
			case 21:
			case 12: tag_ope = 12; break;
			case 32:
			case 23: tag_ope = 23; break;
			default:  break;
			};
		}
		else if (num_fig == 4)
		{
			rand1 = (rand() % 4 + 1) + (rand() % 4 + 1) * 10;
			switch (rand1)
			{
			case 12: tag_ope = 12; break;
			case 13: tag_ope = 13; break;
			case 23: tag_ope = 23; break;
			case 24: tag_ope = 24; break;
			case 34: tag_ope = 34; break;
			default:  break;
			}
		}
		//观察数据
		for (i = 0; i < num_ope; i++)
		{
			printf("%d/%d %c ", figure[i], figure[i + 4], operate[i]);
		}
		printf("%d/%d =\n", figure[i], figure[i + 4]);


		if (CalAnswer(figure, operate, type_fig, num_fig, num_ope, tag_ope, ans) == TRUE)
		{
			title_num++;
			for (i = 0; i < num_ope; i++)
			{
				printf("%d/%d %c ", figure[i], figure[i + 4], operate[i]);
			}
			printf("%d/%d =\n", figure[i], figure[i + 4]);
			WriteFile(figure, operate, type_fig, num_fig, num_ope, tag_ope, question_file);
			WriteAnswer(ans, answer_file);
		}
	}
	printf("全部题目生成成功，请查看txt文件");
	system("pause");
}


//判断真分数是否需要化简
void JudgeNumber(int ans[])
{
	int t;

	if (ans[2] == 1)
	{
		return;
	}
	else
	{
		ans[0] = ans[1] / ans[2];
		ans[1] = ans[1] % ans[2];

		t = gcd(ans[1], ans[2]);

		ans[1] = ans[1] / t;
		ans[2] = ans[2] / t;
	}
}

//判断题目是否重复
void JudgeRepeat()
{

}

//计算答案
Status CalAnswer(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, int ans[])
{
	int sum, i, m, t[2], f[8], tag_have;	//t[0]分子，t[1]分母
	char ope[3];
	t[0] = 0;  t[1] = 1;
	for (i = 0; i < 8; i++)
	{
		f[i] = figure[i];
	}
	for (i = 0; i < num_ope; i++)
	{
		ope[i] = operate[i];
	}

	sum = Sequence(figure, operate, type_fig, num_fig, num_ope, tag_ope);

	m = pow(10, num_ope - 1);
	while (m)
	{
		i = sum / m - 1;
		tag_have = 0;
		if (ope[i] == '+')
		{
			t[0] = f[i] * f[i + 5] + f[i + 1] * f[i + 4];
			t[1] = f[i + 4] * f[i + 5];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		else if (ope[i] == '-')
		{
			t[0] = f[i] * f[i + 5] - f[i + 1] * f[i + 4];
			if (t[0] < 0) return ERROR;		//判断是否出现负数
			t[1] = f[i + 4] * f[i + 5];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		else if (ope[i] == '*')
		{
			t[0] = f[i] * f[i + 1];
			t[1] = f[i + 4] * f[i + 5];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		else if (ope[i] == '/')
		{
			if (f[i + 1] == 0) return ERROR;		//防止被除数为0
			t[0] = f[i] * f[i + 5];
			t[1] = f[i + 1] * f[i + 4];
			f[i] = f[i + 1] = t[0];
			f[i + 4] = f[i + 5] = t[1];
		}
		else return ERROR;

		for (i = 0; i < num_fig; i++)
		{
			if (f[i] == t[0] && f[i + 4] == t[1] && tag_have == 1) break;
			if (f[i] == t[0] && f[i + 4] == t[1] && tag_have == 0) tag_have = 1;
		}
		for (i; i < num_ope; i++)
		{
			f[i] = f[i + 1];
			f[i + 4] = f[i + 5];
			ope[i - 1] = ope[i];
		}
		num_fig--;
		num_ope--;

		switch (sum)
		{
		case 1:  break;
		case 12: sum = 1; break;
		case 21: sum = 1; break;
		case 123:sum = 12; break;
		case 132:sum = 21; break;
		case 213:sum = 12; break;
		case 231:sum = 21; break;
		case 312:sum = 12; break;
		case 321:sum = 21; break;
		default: break;
		}

		printf("t[0]==%d,t[1]==%d\n", t[0], t[1]);

		m /= 10;
	}
	ans[1] = t[0];
	ans[2] = t[1];
	printf("分子=%d,分母=%d\n", ans[1], ans[2]);
	JudgeNumber(ans);

	return TRUE;
}

//题目放入文件
void WriteFile(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file)
{
	if (file == NULL) return;
	printf("生成了第 %d 道\n", title_num);
	int i;
	fprintf(file, "题目%d:   ", title_num);
	if (tag_ope != 10)
	{
		for (i = 0; i < num_ope; i++)
		{
			if (i + 1 == tag_ope / 10) fprintf(file, "(");
			if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);
			else fprintf(file, "%d", figure[i]);
			if (i + 1 == tag_ope % 10) fprintf(file, ")");
			if (operate[i] == '*')
				fprintf(file, "  ×  ");
			else if (operate[i] == '/')
				fprintf(file, "  ÷  ");
			else
				fprintf(file, "  %c  ", operate[i]);
		}
		if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);
		else fprintf(file, "%d", figure[i]);
		if (i + 1 == tag_ope % 10) fprintf(file, ")");
	}
	else
	{
		for (i = 0; i < num_ope; i++)
		{
			if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);
			else fprintf(file, "%d", figure[i]);

			if (operate[i] == '*')
				fprintf(file, "  ×  ");
			else if (operate[i] == '/')
				fprintf(file, "  ÷  ");
			else
				fprintf(file, "  %c  ", operate[i]);
		}
		if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);
		else fprintf(file, "%d", figure[i]);
	}
	fprintf(file, " =\n");
}

//答案放入文件
void WriteAnswer(int ans[], FILE* file)
{
	printf("%d'%d/%d\n", ans[0], ans[1], ans[2]);

	if (ans[1] == 0)
	{
		fprintf(file, "第 %d 题的答案是 %d\n", title_num, ans[0]);
	}
	else
	{
		if (ans[0] == 0)
		{
			fprintf(file, "第 %d 题的答案是 %d", title_num, ans[1]);
		}
		else
		{
			fprintf(file, "第 %d 题的答案是 %d'%d", title_num, ans[0], ans[1]);
		}

		if (ans[2] != 1)
		{
			fprintf(file, "/%d\n", ans[2]);
		}
		else
		{
			fprintf(file, "\n");
		}
	}


	printf("答案已打印。\n\n\n");
}

//计算顺序
int Sequence(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope)
{
	int sum = 0, j;
	if (tag_ope == 12 || tag_ope == 23 || tag_ope == 34 || tag_ope == 13 || tag_ope == 24)
	{
		for (j = tag_ope / 10 - 1; j < tag_ope % 10 - 1; j++)
		{
			if (operate[j] == '*')
			{
				sum = sum * 10 + j + 1;
			}
			else if (operate[j] == '/')
			{
				sum = sum * 10 + j + 1;
			}
		}
		for (j = tag_ope / 10 - 1; j < tag_ope % 10 - 1; j++)
		{
			if (operate[j] == '+')
			{
				sum = sum * 10 + j + 1;
			}
			else if (operate[j] == '-')
			{
				sum = sum * 10 + j + 1;
			}
		}
	}

	for (j = 0; j < num_ope; j++)
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
	for (j = 0; j < num_ope; j++)
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

//求最大公因数
int gcd(int x, int y)
{
	int t;
	while (y > 0)
	{
		t = x % y;
		x = y;
		y = t;
	}
	return x;
}


//答案对比函数

