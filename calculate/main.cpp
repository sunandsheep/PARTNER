#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>

using namespace std;


void CreatQuestions(int number, int range); //������Ŀ
void JudgeNumber(int fenzi, int fenmu, char s[]);  //�ж�������Ƿ���Ҫ����
void JudgeRepeat();    //�ж���Ŀ�Ƿ��ظ�
void CalAnswer(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope, char ans[]);  //�����
void WriteFile(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file);  //��Ŀ�����ļ�
void WriteAnswer(char ans[], FILE* file);  //�𰸷����ļ�
void Sequence(int figure[], char opetate[], int type_fig, int num_fig, int num_ope, int tag_ope);  //����˳��

int main()
{
	int number;
	printf("��������Ŀ����\n");
	scanf("%d", &number);

	int range;
	printf("��������ֵ��Χ\n");
	scanf("%d", &range);

	CreatQuestions(number, range);



	return 0;
}

//������Ŀ
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
		type_fig = rand() % 2;  //0��Ȼ����1�����

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

//�ж�������Ƿ���Ҫ����
void JudgeNumber(int fenzi, int fenmu, char s[])
{

}

//�ж���Ŀ�Ƿ��ظ�
void JudgeRepeat()
{

}

//�����
void CalAnswer(int figure[], char opetate[], int type_fig, int num_fig, int n