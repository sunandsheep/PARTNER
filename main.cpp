#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

struct Question
{
	char name[40];
	char ans[10];
};

void CreatQuestions(int number, int range); //创建题目
void JudgeNumber(string s);  //判断真分数是否需要化简
void JudgeRepeat();    //判断题目是否重复
void CalAnswer(string s);  //计算答案
void WriteFile(string s, FILE* file, int tag)；  //题目、答案放入文件
void Sequence(string s);  //计算顺序

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
	Question question[10000];
}

//判断真分数是否需要化简
void JudgeNumber(string s)
{

}

//判断题目是否重复
void JudgeRepeat()
{

}

//计算答案
void CalAnswer(string s)
{

}

//题目、答案放入文件
void WriteFile(string s, FILE* file, int tag)
{

}

//计算顺序
void Sequence(string s)
{

}