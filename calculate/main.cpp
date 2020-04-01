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
#define EPSILON 0.0001  //浮点数判断相等精度

typedef int Status;
int title_num;		//题号
float answer[10050];	//答案
int seq[10050];			//运算顺序
char OPE[10050][3];		//运算符
int Num_ope[10050];		//运算符数
double Figure[10050][4]; //题目数字
int xuhao;



void CreatQuestions(int number, int range);	//创建题目
void JudgeNumber(int ans[]);		//判断真分数是否需要化简
Status JudgeRepeat(int figure[], char opetate[], int num_ope);				//判断题目是否重复
Status CalAnswer(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, int ans[]);		//计算答案
void WriteFile(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, FILE* file);  //题目放入文件
void WriteAnswer(int ans[], FILE* file);		//答案放入文件
int Sequence(int figure[], char operate[], int num_fig, int num_ope, int tag_ope); //计算顺序
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

	srand(time(NULL));		//确保不是伪随机
	title_num = 0;

	FILE* question_file;	//打开相应文件
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
		int i, rand1, tag_ope = 10;		//tag_ope赋值10
		num_ope = (rand() % 3) + 1;		//确定运算符数
		num_fig = num_ope + 1;			//数字个数 是 运算符数+1

		//数字为自然数时为1，真分数时下面代码会对相应分母赋值
		figure[4] = figure[5] = figure[6] = figure[7] = 1;

		//答案赋值，避免上次结果对这次进行影响
		ans[0] = ans[1] = 0;   ans[2] = 1;

		//确定数字
		for (i = 0; i < num_fig; i++)
		{
			figure[i] = rand() % range;
			type_fig = rand() % 2;		//0自然数，1真分数
			if (type_fig == 1 && figure[i] != 0)	//数字为真分数且分子不为0时
			{
				figure[i + 4] = rand() % range;
				while (figure[i + 4] == 0 || figure[i] % figure[i + 4] == 0)	//分母不能等于0且不组成自然数
				{
					figure[i + 4] = rand() % range;
				}
				t = gcd(figure[i], figure[i + 4]);		//化简
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
		if (num_fig == 3)		//数字个数为3
		{
			//tag_ope = 12 表示前括号在第一个数字前，后括号在第二个数字后
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

		//判断创建的题目是否合法以及是否重复
		if (CalAnswer(figure, operate, num_fig, num_ope, tag_ope, ans) == TRUE && JudgeRepeat(figure, operate, num_ope) == ERROR)
		{

			title_num++;

			WriteFile(figure, operate, num_fig, num_ope, tag_ope, question_file);	//题目写入文件
			WriteAnswer(ans, answer_file);											//答案写入文件
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
Status JudgeRepeat(int figure[], char operate[], int num_ope)
{
	int n1, n2, n3, i, j, x, sum, m;
	i = title_num;

	sum = seq[i];
	m = pow(10, num_ope - 1);

	//符号放入全局数组
	for (j = 0; j < num_ope; j++)
	{
		x = sum / m - 1;
		OPE[i][j] = operate[x];

		sum = sum % m;
		m = m / 10;
	}

	//数据放入全局数组
	switch (seq[i])
	{
	case 1:  Figure[i][0] = figure[0] * 1.0 / figure[4]; Figure[i][1] = figure[1] * 1.0 / figure[5]; break;
	case 12: Figure[i][0] = figure[0] * 1.0 / figure[4]; Figure[i][1] = figure[1] * 1.0 / figure[5];
		Figure[i][2] = figure[2] * 1.0 / figure[6]; break;
	case 21: Figure[i][0] = figure[1] * 1.0 / figure[5]; Figure[i][1] = figure[2] * 1.0 / figure[6];
		Figure[i][2] = figure[0] * 1.0 / figure[4]; break;
	case 123:Figure[i][0] = figure[0] * 1.0 / figure[4]; Figure[i][1] = figure[1] * 1.0 / figure[5];
		Figure[i][2] = figure[2] * 1.0 / figure[6]; Figure[i][3] = figure[3] * 1.0 / figure[7]; break;
	case 132:Figure[i][0] = figure[0] * 1.0 / figure[4]; Figure[i][1] = figure[1] * 1.0 / figure[5];
		Figure[i][2] = figure[2] * 1.0 / figure[6]; Figure[i][3] = figure[3] * 1.0 / figure[7]; break;
	case 213:Figure[i][0] = figure[1] * 1.0 / figure[5]; Figure[i][1] = figure[2] * 1.0 / figure[6];
		Figure[i][2] = figure[0] * 1.0 / figure[4]; Figure[i][3] = figure[3] * 1.0 / figure[7]; break;
	case 231:Figure[i][0] = figure[1] * 1.0 / figure[5]; Figure[i][1] = figure[2] * 1.0 / figure[6];
		Figure[i][2] = figure[3] * 1.0 / figure[7]; Figure[i][3] = figure[0] * 1.0 / figure[4]; break;
	case 312:Figure[i][0] = figure[2] * 1.0 / figure[6]; Figure[i][1] = figure[3] * 1.0 / figure[7];
		Figure[i][2] = figure[0] * 1.0 / figure[4]; Figure[i][3] = figure[1] * 1.0 / figure[5]; break;
	case 321:Figure[i][0] = figure[2] * 1.0 / figure[6]; Figure[i][1] = figure[3] * 1.0 / figure[7];
		Figure[i][2] = figure[1] * 1.0 / figure[5]; Figure[i][3] = figure[0] * 1.0 / figure[4]; break;
	default: break;
	}

	//遍历全局数组，查询是否有重复的
	for (n1 = 0; n1 < i; n1++)
	{
		xuhao = n1 + 1;
		if (fabs(answer[i] - answer[n1]) < EPSILON && Num_ope[i] == Num_ope[n1])	//答案相等、运算符数相等
		{
			//按运算顺序，判断符号是否相等
			for (n2 = 0; n2 < num_ope; n2++)
			{
				if (OPE[i][n2] != OPE[n1][n2]) break;

				if (n2 == num_ope - 1)
				{
					//数字比对
					for (n3 = 0; n3 < num_ope; n3++)
					{
						if (n3 == 0)
						{
							if (OPE[i][n3] == '-' || OPE[i][n3] == '/')
							{
								//对于第一次运算，‘-’和‘/’运算顺序不能交换，如果相同则进行下一个判断
								if (fabs(Figure[i][n3] - Figure[n1][n3]) >= EPSILON || fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) >= EPSILON)
									break;
							}
							else
							{
								//对于第一次运算，数据可交换，判断数据是否一致
								if ((fabs(Figure[i][0] - Figure[n1][0]) < EPSILON && fabs(Figure[i][1] - Figure[n1][1]) < EPSILON)
									|| (fabs(Figure[i][0] - Figure[n1][1]) < EPSILON && fabs(Figure[i][1] - Figure[n1][0]) < EPSILON))
								{
									//如果运算符数只有一个，则题目重复
									if (num_ope == 1) {
										printf("%.5f   %.5f   %.5f     %.5f\n", Figure[i][0], Figure[i][1], Figure[n1][0], Figure[n1][1]);
										printf("第%d题与第%d题重复\n", title_num + 1, xuhao);
										printf("n3==0");		//判断重复测试是否成功的输出标志
										return TRUE;			//重复返回TRUE，不重复则进行下一个判断
									}
								}
								else break;
							}

						}

						if (n3 == 1)
						{
							if (seq[i] == 132 || seq[i] == 312)		//特殊运算顺序处理
							{
								if (OPE[i][n3] == '-' || OPE[i][n3] == '/')
								{
									if (fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) >= EPSILON || fabs(Figure[i][n3 + 2] - Figure[n1][n3 + 2]) >= EPSILON)
										break;
									else { printf("n3==1.1\n"); return TRUE; }	//所有数据对比完成相同，重复
								}
								else
								{
									//判断可交换时，是否数据相同
									if (
										(fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) < EPSILON && fabs(Figure[i][n3 + 2] - Figure[n1][n3 + 2]) < EPSILON)
										||
										(fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 2]) < EPSILON && fabs(Figure[i][n3 + 2] - Figure[n1][n3 + 1]) < EPSILON)
										)
									{
										printf("n3==1.2\n"); return TRUE;
									}	//所有数据比对全部相同，重复
									else return ERROR;
								}
							}
							else
							{
								//其他情况下，第一次运算的数字，第二次运算只涉及一个数字第一次被使用
								if (fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) >= EPSILON) break;
							}
						}

						if (n3 == 2)
						{
							if (fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) >= EPSILON) break;
							else { printf("n3==3\n"); return TRUE; }
						}
					}
				}
			}
		}
	}
	return ERROR;	//答案不相等，不重复
}

//计算答案
Status CalAnswer(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, int ans[])
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

	sum = Sequence(figure, operate, num_fig, num_ope, tag_ope);
	seq[title_num] = sum;
	Num_ope[title_num] = num_ope;

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
			if (t[0] < 0) return ERROR;		//判断计算过程是否出现负数,如出现，不合法
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
			if (f[i + 1] == 0) return ERROR;		//防止被除数为0，如出现，不合法
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

		m /= 10;
	}
	ans[1] = t[0];
	ans[2] = t[1];

	answer[title_num] = ans[1] * 1.0 / ans[2];

	JudgeNumber(ans);

	return TRUE;
}

//题目放入文件
void WriteFile(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, FILE* file)
{
	if (file == NULL) return;
	printf("生成了第 %d 道\n", title_num);
	int i;
	fprintf(file, "题目%d:   ", title_num);
	if (tag_ope != 10)		//题目包含括号
	{
		for (i = 0; i < num_ope; i++)
		{
			if (i + 1 == tag_ope / 10) fprintf(file, "(");
			if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);  //有分母则按分数输出
			else fprintf(file, "%d", figure[i]);
			if (i + 1 == tag_ope % 10) fprintf(file, ")");
			if (operate[i] == '*')			//输出运算符
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
int Sequence(int figure[], char operate[], int num_fig, int num_ope, int tag_ope)
{
	int sum = 0, j;
	//sum = 231 表示先运算顺序为： 第2个运算符-->第3个运算符-->第1个运算符

	if (tag_ope == 12 || tag_ope == 23 || tag_ope == 34 || tag_ope == 13 || tag_ope == 24)  //如果有括号
	{
		for (j = tag_ope / 10 - 1; j < tag_ope % 10 - 1; j++)	//j为相应序号
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

	for (j = 0; j < num_ope; j++)	//对所有运算符遍历
	{
		if (operate[j] == '*' && j + 1 != sum % 10 && j + 1 != sum / 10)	//括号中运行过的不再放入
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
