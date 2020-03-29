#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>

using namespace std;


void CreatQuestions(int number, int range); //创建题目
void JudgeNumber(int fenzi, int fenmu, char s[]);  //判断真分数是否需要化简
void JudgeRepeat();    //判断题目是否重复
void CalAnswer(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope, char ans[]);  //计算答案
void WriteFile(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file);  //题目放入文件
void WriteAnswer(char ans[], FILE* file);  //答案放入文件
void Sequence(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope);  //计算顺序

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
	int num_ope, type_ope, num_fig, type_fig;
	int figure[8];
	char operate[3];

	srand(time(NULL));

	while (number)
	{
		int i, rand1, tag_ope;
		num_ope = (rand() % 3) + 1;
		type_fig = rand() % 2;  //0自然数，1真分数

		if (type_fig == 0)
		{
			num_fig = num_ope + 1;
			for (i = 0; i < num_fig; i++)
			{
				figure[i] = rand() % range;
			}
			for (i = 0; i < num_ope; i++)
			{
				rand1 = rand() % 4;
				switch (rand1)
				{
				case 0: operate[i] = '+'; break;
				case 1: operate[i] = '-'; break;
				case 2: operate[i] = '*'; break;
				case 3: operate[i] = '/'; break;
				default:break;
				}
			}

			rand1 = rand() % 4;
			switch (rand1)
			{
			case 0:
			case 1:
			case 2: tag_ope = 0; break;
			case 3: tag_ope = 1; break;
			default:break;
			}


		}
		else
		{
			num_fig = (num_ope + 1) * 2;
		}

		number--;
	}

}

//判断真分数是否需要化简
void JudgeNumber(int fenzi, int fenmu, char s[])
{

}

//判断题目是否重复
void JudgeRepeat()
{

}

//计算答案
void CalAnswer(int figure[], char opetate[], int type_fig, int num_fig, int n