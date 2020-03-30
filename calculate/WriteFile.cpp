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


void WriteFile(int figure[], char operate[], int type_fig, int num_fig, int num_ope, int tag_ope, FILE* file)
{
	printf("�����˵� %d ��\n", title_num);
	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		if (type_fig == 0)     //��ֵ������Ȼ��
		{
			if (tag_ope == 10)    //���ʽ��û������
			{
				fprintf(file, "%d.  ", title_num);
				for (int i = 0; i < num_fig; i++)
				{
					fprintf(file, "%d  ", figure[i]);
					if (i + 1 < num_fig)
						fprintf(file, "%c  ", operate[i]);
				}
				fputs("\r\n", file);
			}
			else if (tag_ope != 10)       //���ʽ��������
			{
				switch (num_fig)
				{
				case 3:
					if (tag_ope == 12)
						fprintf(file, "%d.   (%d  %c  %d)  %c  %d", title_num, figure[0], operate[0], figure[1], operate[1], figure[2]);
					else if (tag_ope == 23)
						fprintf(file, "%d.   %d  %c  (%d  %c  %d)", title_num, figure[0], operate[0], figure[1], operate[1], figure[2]);
					else
						cout << "����λ�ô���" << endl;
					break;
				case 4:
					switch (tag_ope)
					{
					case 12: fprintf(file, "%d.   (%d  %c  %d)  %c  %d  %c  %d", title_num, figure[0], operate[0], figure[1], operate[1], figure[2], operate[2], figure[3]); break;
					case 13: fprintf(file, "%d.   (%d  %c  %d  %c  %d)  %c  %d", title_num, figure[0], operate[0], figure[1], operate[1], figure[2], operate[2], figure[3]); break;
					case 23: fprintf(file, "%d.   %d  %c  (%d  %c  %d)  %c  %d", title_num, figure[0], operate[0], figure[1], operate[1], figure[2], operate[2], figure[3]); break;
					case 24: fprintf(file, "%d.   %d  %c  (%d  %c  %d  %c  %d)", title_num, figure[0], operate[0], figure[1], operate[1], figure[2], operate[2], figure[3]); break;
					case 34: fprintf(file, "%d.   %d  %c  %d  %c  (%d  %c  %d)", title_num, figure[0], operate[0], figure[1], operate[1], figure[2], operate[2], figure[3]); break;
					default:break;
					}
				}
				fputs("\r\n", file);
			}
			else
				cout << "����λ�ô���������Ŀʧ��" << endl;
		}

		else if (type_fig == 1)    //��ֵ���з���
		{
			if (tag_ope == 10)       //���ʽ������
			{
				fprintf(file, "%d.  ", title_num);
				for (int i = 0; i < num_fig; i++)
				{
					if (figure[i] % figure[i + 4] == 0)
						fprintf(file, "%d  ", figure[i]);
					else
						fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
					if (i + 1 < num_fig)
						fprintf(file, "%c  ", operate[i]);
				}
				fputs("\r\n", file);
			}

			else if (tag_ope != 10)    //���ʽ������
			{
				fprintf(file, "%d.  ", title_num);
				switch (num_fig)
				{
				case 3:
					if (tag_ope == 12)
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 0)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 1)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 1)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
					else if (tag_ope == 23)
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 1)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 2)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 2)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
					else
						cout << "����λ�ô���,������Ŀʧ��" << endl;
					fputs("\r\n", file);
					break;


				case 4:
					switch (tag_ope)
					{
					case 12:
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 0)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 1)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 1)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
						break;

					case 13:
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 0)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 2)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 2)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
						break;

					case 23:
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 1)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 2)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 2)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
						break;

					case 24:
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 1)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 3)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 3)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
						break;

					case 34:
						for (int i = 0; i < num_fig; i++)
						{
							if (i == 2)
								fprintf(file, "(");
							if (figure[i] % figure[i + 4] == 0)
							{
								fprintf(file, "%d  ", figure[i]);
								if (i == 3)
									fprintf(file, ")");
							}
							else {
								fprintf(file, "%d/%d  ", figure[i], figure[i + 4]);
								if (i == 3)
									fprintf(file, ")");
							}
							if (i + 1 < num_fig)
								fprintf(file, "%c  ", operate[i]);
						}
						break;

					default:cout << "����λ�ô���������Ŀʧ��" << endl; break;  //����λ��ѡ��

					}

					fputs("\r\n", file);
					break;

				default:break;       // ����������ѡ��
				}
			}
		}
	}
}


void WriteAnswer(char ans[], FILE* file)
{
	fprintf(file, "�� %d ��Ĵ��� %s", title_num, ans);
	fputs("\r\n", file);
	printf("���Ѵ�ӡ��");
}


