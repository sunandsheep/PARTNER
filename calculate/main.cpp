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

int title_num;
typedef int Status;


void CreatQuestions(int number, int range);	//������Ŀ
void JudgeNumber(int fenzi, int fenmu, char s[]);		//�ж�������Ƿ���Ҫ����
void JudgeRepeat();				//�ж���Ŀ�Ƿ��ظ�
Status CalAnswer(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, char ans[]);		//�����
void WriteFile(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file);  //��Ŀ�����ļ�
void WriteAnswer(char ans[], FILE* file);		//�𰸷����ļ�
int Sequence(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope);		//����˳��



int main()
{
	int number,range;
	FILE* question_file;
	FILE* answer_file;


	printf("��������Ŀ����\n");
	scanf("%d", &number);
	printf("��������ֵ��Χ\n");
	scanf("%d", &range);
	CreatQuestions(number, range);

	if ((question_file = fopen("Exercise.txt", "a+")) == NULL)
	{
		cout << "You can't open the file!\n" << endl;
		exit(1);
	}
	if ((answer_file = fopen("Answers.txt", "a+")) == NULL)
	{
		cout << "You can't open the file!\n" << endl;
		exit(1);
	}


	return 0;
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
void CalAnswer(int figure[], char opetate[], int type_fig, int num_fig, int n)
{


}



