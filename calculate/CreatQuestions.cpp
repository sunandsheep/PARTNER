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



//创建题目
void CreatQuestions(int number, int range)
{
	int num_ope, type_ope, num_fig, type_fig;
	int figure[8];
	char operate[3];

	figure[4] = figure[5] = figure[6] = figure[7] = 1;

	srand(time(NULL));

	while (number)
	{
		int i, rand1, tag_ope = 10;
		num_ope = (rand() % 3) + 1;
		num_fig = num_ope + 1;

		//确定数字
		for (i = 0; i < num_fig; i++)
		{
			figure[i] = rand() % range;
			type_fig = rand() % 2;		//0自然数，1真分数
			if (type_fig == 1)
			{
				figure[i + 4] = rand() % range;
				while (figure[i + 4] == 0 || figure[i] % figure[i + 4] == 0)
				{
					figure[i + 4] = rand() % range;
				}
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
		if (num_ope == 3)
		{
			rand1 = (rand() % 3 + 1) + (rand() % 3 + 1) * 10;
			switch (rand1)
			{
			case 12: tag_ope = 12; break;
			case 23: tag_ope = 23; break;
			default:  break;
			};
		}
		else if (num_ope == 4)
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


		//非负判断

		number--;
	}

}

