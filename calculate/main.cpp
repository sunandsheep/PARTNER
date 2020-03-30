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


void CreatQuestions(int number, int range);	//创建题目
void JudgeNumber(int fenzi, int fenmu, char s[]);		//判断真分数是否需要化简
void JudgeRepeat();				//判断题目是否重复
Status CalAnswer(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, char ans[]);		//计算答案
void WriteFile(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file);  //题目放入文件
void WriteAnswer(char ans[], FILE* file);		//答案放入文件
int Sequence(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope);		//计算顺序



int main()
{
	int number,range;
	FILE* question_file;
	FILE* answer_file;


	printf("请输入题目个数\n");
	scanf("%d", &number);
	printf("请输入数值范围\n");
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




//判断真分数是否需要化简
void JudgeNumber(int fenzi, int fenmu, char s[])
{

}

//判断题目是否重复
void JudgeRepeat()
{

}

//计算答案
void CalAnswer(int figure[], char opetate[], int type_fig, int num_fig, int n)
{


}



