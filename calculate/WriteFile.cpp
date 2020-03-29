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
	int QuestionNum;
};


void WriteFile(Question problem, FILE* file, int tag)
{
	FILE *fp;
	char *connet,biaodian[] =".";

	sprintf(connet, "%d", problem.QuestionNum);
	strcat(connet, biaodian);

	if (tag == 0)
	{
		strcat(connet, problem.name);
		if ((fp = fopen("Exercises.txt", "a+")) == NULL)
		{
			cout << "You can't open the file!\n" << endl;
			exit(1);
		}
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			fputs(connet, fp);
			fputs("\r\n", fp);
			fclose(fp);
		}
	}
	else if (tag == 1)
	{
		strcat(connet, problem.ans);
		if ((fp = fopen("Answers.txt.txt", "a+")) == NULL)
		{
			cout << "You can't open the file!\n" << endl;
			exit(1);
		}
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			fputs(connet, fp);
			fputs("\r\n", fp);
			fclose(fp);
		}
	}
	else
		cout << "tagÊäÈë´íÎó" << endl;
}