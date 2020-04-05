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
#define EPSILON 0.0001  //�������ж���Ⱦ���

typedef int Status;
int title_num;		//���
float answer[10050];	//��
int seq[10050];			//����˳��
char OPE[10050][3];		//�����
int Num_ope[10050];		//�������
double Figure[10050][4]; //��Ŀ����
int xuhao;


void CreatQuestions(int number, int range);	//������Ŀ
void JudgeNumber(int ans[]);		//�ж�������Ƿ���Ҫ����
Status JudgeRepeat(int figure[], char opetate[], int num_ope);				//�ж���Ŀ�Ƿ��ظ�
Status CalAnswer(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, int ans[]);		//�����
void WriteFile(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, FILE* file);  //��Ŀ�����ļ�
void WriteAnswer(int ans[], FILE* file);		//�𰸷����ļ�
int Sequence(int figure[], char operate[], int num_fig, int num_ope, int tag_ope); //����˳��
int gcd(int x, int y);		//���������
int ChangeNumber(char* question_read, int i[]);//�������ַ���ת��Ϊ��������
void CanShu(int change, char* question_read, int i[], int ctag_ope[], int fig_num[], int ope_num[], int figure[], int ans[], char operate[]);//�ó�����������Ĳ���
void CompareAnswer();          //�𰸱ȽϺ���
void ChangeAnswer(int ans[], char answer_cal[][20]);     //�Ѽ�����Ľ��ת��Ϊ�ַ���

int main()
{
	int number;
	char operate, judge = 'y';
	cout << "----------��ӭʹ�������������-----------" << endl;
	cout << "        1.������Ŀ��" << endl;
	cout << "        2.��������Ŀ�ʹ𰸽����ж���" << endl;

	while (judge == 'y')
	{
		cout << "        �������������Ĳ���������1����2��" << endl;
		cin >> operate;
		if (operate == '1') {
			printf("��������Ŀ����\n");
			scanf("%d", &number);

			int range;
			printf("��������ֵ��Χ\n");
			scanf("%d", &range);

			CreatQuestions(number, range);
		}
		else if (operate == '2')
			CompareAnswer();
		else
			cout << "�������" << endl;
		cout << "��Ҫ��������������y��n" << endl;
		cin >> judge;
	}
	system("pause");
	return 0;
}

//������Ŀ
void CreatQuestions(int number, int range)
{
	int num_ope, num_fig, type_fig, t;
	int figure[8], ans[3];
	char operate[3];

	srand(time(NULL));		//ȷ������α���
	title_num = 0;

	FILE* question_file;	//����Ӧ�ļ�
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
		int i, rand1, tag_ope = 10;		//tag_ope��ֵ10
		num_ope = (rand() % 3) + 1;		//ȷ���������
		num_fig = num_ope + 1;			//���ָ��� �� �������+1

										//����Ϊ��Ȼ��ʱΪ1�������ʱ�����������Ӧ��ĸ��ֵ
		figure[4] = figure[5] = figure[6] = figure[7] = 1;

		//�𰸸�ֵ�������ϴν������ν���Ӱ��
		ans[0] = ans[1] = 0;   ans[2] = 1;

		//ȷ������
		for (i = 0; i < num_fig; i++)
		{
			figure[i] = rand() % range;
			type_fig = rand() % 2;		//0��Ȼ����1�����
			if (type_fig == 1 && figure[i] != 0)	//����Ϊ������ҷ��Ӳ�Ϊ0ʱ
			{
				figure[i + 4] = rand() % range;
				while (figure[i + 4] == 0 || figure[i] % figure[i + 4] == 0)	//��ĸ���ܵ���0�Ҳ������Ȼ��
				{
					figure[i + 4] = rand() % range;
				}
				t = gcd(figure[i], figure[i + 4]);		//����
				figure[i] = figure[i] / t;
				figure[i + 4] = figure[i + 4] / t;
			}
		}

		//ȷ������
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

		//ȷ���Ƿ������ż�����λ��
		if (num_fig == 3)		//���ָ���Ϊ3
		{
			//tag_ope = 12 ��ʾǰ�����ڵ�һ������ǰ���������ڵڶ������ֺ�
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

		//�жϴ�������Ŀ�Ƿ�Ϸ��Լ��Ƿ��ظ�
		if (CalAnswer(figure, operate, num_fig, num_ope, tag_ope, ans) == TRUE && JudgeRepeat(figure, operate, num_ope) == ERROR)
		{

			title_num++;

			WriteFile(figure, operate, num_fig, num_ope, tag_ope, question_file);	//��Ŀд���ļ�
			WriteAnswer(ans, answer_file);											//��д���ļ�
		}
	}
	printf("ȫ����Ŀ���ɳɹ�����鿴txt�ļ�");
	system("pause");
}


//�ж�������Ƿ���Ҫ����
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

//�ж���Ŀ�Ƿ��ظ�
Status JudgeRepeat(int figure[], char operate[], int num_ope)
{
	int n1, n2, n3, i, j, x, sum, m;
	i = title_num;

	sum = seq[i];
	m = pow(10, num_ope - 1);

	//���ŷ���ȫ������
	for (j = 0; j < num_ope; j++)
	{
		x = sum / m - 1;
		OPE[i][j] = operate[x];

		sum = sum % m;
		m = m / 10;
	}

	//���ݷ���ȫ������
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

	//����ȫ�����飬��ѯ�Ƿ����ظ���
	for (n1 = 0; n1 < i; n1++)
	{
		xuhao = n1 + 1;
		if (fabs(answer[i] - answer[n1]) < EPSILON && Num_ope[i] == Num_ope[n1])	//����ȡ�����������
		{
			//������˳���жϷ����Ƿ����
			for (n2 = 0; n2 < num_ope; n2++)
			{
				if (OPE[i][n2] != OPE[n1][n2]) break;

				if (n2 == num_ope - 1)
				{
					//���ֱȶ�
					for (n3 = 0; n3 < num_ope; n3++)
					{
						if (n3 == 0)
						{
							if (OPE[i][n3] == '-' || OPE[i][n3] == '/')
							{
								//���ڵ�һ�����㣬��-���͡�/������˳���ܽ����������ͬ�������һ���ж�
								if (fabs(Figure[i][n3] - Figure[n1][n3]) >= EPSILON || fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) >= EPSILON)
									break;
							}
							else
							{
								//���ڵ�һ�����㣬���ݿɽ������ж������Ƿ�һ��
								if ((fabs(Figure[i][0] - Figure[n1][0]) < EPSILON && fabs(Figure[i][1] - Figure[n1][1]) < EPSILON)
									|| (fabs(Figure[i][0] - Figure[n1][1]) < EPSILON && fabs(Figure[i][1] - Figure[n1][0]) < EPSILON))
								{
									//����������ֻ��һ��������Ŀ�ظ�
									if (num_ope == 1) {
										printf("%.5f   %.5f   %.5f     %.5f\n", Figure[i][0], Figure[i][1], Figure[n1][0], Figure[n1][1]);
										printf("��%d�����%d���ظ�\n", title_num + 1, xuhao);
										printf("n3==0");		//�ж��ظ������Ƿ�ɹ��������־
										return TRUE;			//�ظ�����TRUE�����ظ��������һ���ж�
									}
								}
								else break;
							}

						}

						if (n3 == 1)
						{
							if (seq[i] == 132 || seq[i] == 312)		//��������˳����
							{
								if (OPE[i][n3] == '-' || OPE[i][n3] == '/')
								{
									if (fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) >= EPSILON || fabs(Figure[i][n3 + 2] - Figure[n1][n3 + 2]) >= EPSILON)
										break;
									else { printf("n3==1.1\n"); return TRUE; }	//�������ݶԱ������ͬ���ظ�
								}
								else
								{
									//�жϿɽ���ʱ���Ƿ�������ͬ
									if (
										(fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 1]) < EPSILON && fabs(Figure[i][n3 + 2] - Figure[n1][n3 + 2]) < EPSILON)
										||
										(fabs(Figure[i][n3 + 1] - Figure[n1][n3 + 2]) < EPSILON && fabs(Figure[i][n3 + 2] - Figure[n1][n3 + 1]) < EPSILON)
										)
									{
										printf("n3==1.2\n"); return TRUE;
									}	//�������ݱȶ�ȫ����ͬ���ظ�
									else return ERROR;
								}
							}
							else
							{
								//��������£���һ����������֣��ڶ�������ֻ�漰һ�����ֵ�һ�α�ʹ��
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
	return ERROR;	//�𰸲���ȣ����ظ�
}

//�����
Status CalAnswer(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, int ans[])
{
	int sum, i, m, t[2], f[8], tag_have;	//t[0]���ӣ�t[1]��ĸ
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
			if (t[0] < 0) return ERROR;		//�жϼ�������Ƿ���ָ���,����֣����Ϸ�
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
			if (f[i + 1] == 0) return ERROR;		//��ֹ������Ϊ0������֣����Ϸ�
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

//��Ŀ�����ļ�
void WriteFile(int figure[], char operate[], int num_fig, int num_ope, int tag_ope, FILE* file)
{
	if (file == NULL) return;
	if (title_num != 1) fprintf(file, "\n");
	printf("�����˵� %d ��\n", title_num);
	int i;
	fprintf(file, "��Ŀ%d:   ", title_num);
	if (tag_ope != 10)		//��Ŀ��������
	{
		for (i = 0; i < num_ope; i++)
		{
			if (i + 1 == tag_ope / 10) fprintf(file, "(");
			if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);  //�з�ĸ�򰴷������
			else fprintf(file, "%d", figure[i]);
			if (i + 1 == tag_ope % 10) fprintf(file, ")");
			if (operate[i] == '*')			//��������
				fprintf(file, "  *  ");
			else if (operate[i] == '/')
				fprintf(file, "  /  ");
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
				fprintf(file, "  *  ");
			else if (operate[i] == '/')
				fprintf(file, "  /  ");
			else
				fprintf(file, "  %c  ", operate[i]);
		}
		if (figure[i + 4] != 1) fprintf(file, "%d/%d", figure[i], figure[i + 4]);
		else fprintf(file, "%d", figure[i]);
	}
	fprintf(file, " =");
}

//�𰸷����ļ�
void WriteAnswer(int ans[], FILE* file)
{
	if (ans[1] == 0)
	{
		fprintf(file, "�� %d ��Ĵ��� %d\n", title_num, ans[0]);
	}
	else
	{
		if (ans[0] == 0)
		{
			fprintf(file, "�� %d ��Ĵ��� %d", title_num, ans[1]);
		}
		else
		{
			fprintf(file, "�� %d ��Ĵ��� %d'%d", title_num, ans[0], ans[1]);
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


	printf("���Ѵ�ӡ��\n\n\n");
}

//����˳��
int Sequence(int figure[], char operate[], int num_fig, int num_ope, int tag_ope)
{
	int sum = 0, j;
	//sum = 231 ��ʾ������˳��Ϊ�� ��2�������-->��3�������-->��1�������

	if (tag_ope == 12 || tag_ope == 23 || tag_ope == 34 || tag_ope == 13 || tag_ope == 24)  //���������
	{
		for (j = tag_ope / 10 - 1; j < tag_ope % 10 - 1; j++)	//jΪ��Ӧ���
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

	for (j = 0; j < num_ope; j++)	//���������������
	{
		if (operate[j] == '*' && j + 1 != sum % 10 && j + 1 != sum / 10)	//���������й��Ĳ��ٷ���
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

//���������
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


//�𰸶ԱȺ���
void CompareAnswer()
{	//������Ŀ����
	int cnum_ope, ctag_ope[3], i[2], fig_num[2], ope_num[2];
	int figure[8], ans[3];
	char operate[4];
	char answer_cal[6][20];
	//��ȡ�ļ�����
	char  question_read[100];
	char answer_read[50];
	//�������	
	int correct_num = 0, wrong_num = 0, title_n = 1;
	int correct_tn[10000], wrong_tn[10000];

	FILE* question_file;
	FILE* answer_file;
	FILE* Grade_file;
	char exercise[20], answer[20];


	cout << "��������ϰ���ļ���" << endl;
	cin >> exercise;
	cout << "��������ļ���" << endl;
	cin >> answer;
	if ((question_file = fopen(exercise, "r")) == NULL)
	{
		printf("You can't open the file!\n");
		exit(1);
	}
	if ((answer_file = fopen(answer, "r")) == NULL)
	{
		printf("You can't open the file!\n");
		exit(1);
	}
	/*
	if ((question_file = fopen("Exercise.txt", "r")) == NULL)
	{
	printf("You can't open the file!\n");
	exit(1);
	}
	if ((answer_file = fopen("Answers.txt", "r")) == NULL)
	{
	printf("You can't open the file!\n");
	exit(1);
	}
	*/
	printf("��ʼ����\n");

	while (!feof(question_file))
	{
		cout << "\n";
		fgets(question_read, 100, question_file);  //����
		fgets(answer_read, 50, answer_file);
		printf("%s", question_read);

		int change = -1;
		ope_num[0] = 0, fig_num[0] = 0;
		ctag_ope[0] = ctag_ope[2] = 0, ctag_ope[1] = 1, i[0] = 0;
		for (int f = 0; f < 8; f++) {
			figure[f] = 1;
		}
		//�𰸸�ֵ�������ϴν������ν���Ӱ��
		ans[0] = ans[1] = 0;   ans[2] = 1;

		//������Ŀ
		for (*i = 8; question_read[i[0]] != '='; i[0]++)
		{
			change = ChangeNumber(question_read, i);  //���ַ�ת��Ϊ����

			CanShu(change, question_read, i, ctag_ope, fig_num, ope_num, figure, ans, operate);  //�ó�����
		}

		cnum_ope = *fig_num - 1;
		ctag_ope[0] = ctag_ope[1] * 10 + ctag_ope[2];

		CalAnswer(figure, operate, *fig_num, cnum_ope, ctag_ope[0], ans);  //���ò��������

		ChangeAnswer(ans, answer_cal);   //�Ѵ�ת��Ϊ�ַ���
		cout << "������Ĵ�:" << answer_cal[0] << endl;

		//��������Ĵ��ַ����������ַ�����������
		char ans_compare[20] = "0";
		int c = 0;
		for (int j = 10; answer_read[j] != '\0'; j++)
		{
			if ((answer_read[j] >= '0' && answer_read[j] <= '9') || answer_read[j] == 39 || answer_read[j] == '/')
			{
				ans_compare[c] = answer_read[j];
				c++;
			}
		}
		cout << "��ȡ�Ĵ𰸣�" << ans_compare << endl;

		if (0 == strcmp(answer_cal[0], ans_compare))  //�Ƚϴ��Ƿ���ȷ
		{
			correct_tn[correct_num] = title_n;
			correct_num++;
		}
		else
		{
			wrong_tn[wrong_num] = title_n;
			wrong_num++;
		}
		title_n++;
	}



	if ((Grade_file = fopen("Grade.txt", "a+")) == NULL)
	{
		printf("You can't open the file!\n");
		exit(1);
	}
	//ͳ����ȷ�������
	fprintf(Grade_file, "Correct :%d", correct_num);
	if (correct_num != 0)
		fprintf(Grade_file, "(");
	for (int correct = 0; correct < correct_num; correct++)
	{

		fprintf(Grade_file, "%d,", correct_tn[correct]);
		if (correct + 1 == correct_num)
			fprintf(Grade_file, ")\n");
	}

	fprintf(Grade_file, "Wrong :%d", wrong_num);
	if (wrong_num != 0)
		fprintf(Grade_file, "(");
	for (int wrong = 0; wrong < wrong_num; wrong++)
	{
		fprintf(Grade_file, "%d,", wrong_tn[wrong]);
		if (wrong + 1 == wrong_num)
			fprintf(Grade_file, ")\n");
	}


	fclose(question_file);
	fclose(answer_file);

}

int ChangeNumber(char* question_read, int *i)    //�������ַ���ת��Ϊ��������
{
	int change = -1;

	if (question_read[*i] >= '0' && question_read[*i] <= '9')
	{
		if (question_read[*i + 1] >= '0' && question_read[*i + 1] <= '9')
			if (question_read[*i + 2] >= '0' && question_read[*i + 2] <= '9')
			{
				change = (question_read[*i] - 48) * 100 + (question_read[*i + 1] - 48) * 10 + (question_read[*i + 2] - 48);
				*i += 2;
				// ת�ɰ�λ��  
			}
			else
			{
				change = (question_read[*i] - 48) * 10 + (question_read[*i + 1] - 48);
				*i += 1;
				//  ת��ʮλ�� 
			}
		else
		{
			change = question_read[*i] - 48;
			// ת�ɸ�λ��  
		}
		return change;
	}
	return -1;
}

void CanShu(int change, char* question_read, int i[], int ctag_ope[], int fig_num[], int ope_num[], int figure[], int ans[], char operate[]) //�ó�����������Ĳ���
{
	char fuhao[3] = "0";
	int tag = 100;
	if (change >= 0)
	{
		for (int c = 3; c > 0; c--)
		{
			if (change >= tag)   //�ж�������λ��
			{
				if (question_read[*i - c] == '/')    //����ǰ�зֺ��򽫸�����Ϊ��ĸ
				{
					figure[(*fig_num) + 3] = change;
				}
				else
				{
					figure[*fig_num] = change;  //���������������ż�һ
					(*fig_num)++;
				}
				if (question_read[*i - c] == '(')   //����ǰ���������¼��λ��
				{
					ctag_ope[1] = *fig_num;
				}
				break;
			}
			if (tag == 10)
				tag = 0;
			else
				tag /= 10;
		}
		if (question_read[*i + 1] == ')')
		{
			ctag_ope[2] = *fig_num;
		}
	}
	else
	{
		if (question_read[*i] == ' ' && question_read[*i + 1] == ' ')   //��ȡ�����
		{
			if (question_read[*i + 2] == '+' || question_read[*i + 2] == '-' || question_read[*i + 2] == '*' || question_read[*i + 2] == '/')
			{
				operate[*ope_num] = question_read[*i + 2];
				(*ope_num)++;
			}
		}
	}
}

void ChangeAnswer(int ans[], char answer_cal[][20])    //�Ѽ�����Ľ��ת��Ϊ�ַ���
{	//ar0������ar1��������ar2����ӣ�ar3���ĸ,ar4��',ar5��/
	strcpy(answer_cal[0], "0");
	strcpy(answer_cal[1], "0");
	strcpy(answer_cal[2], "0");
	strcpy(answer_cal[3], "0");
	strcpy(answer_cal[4], "'");
	strcpy(answer_cal[5], "/");
	if (ans[1] == 0)
	{
		_itoa(ans[0], answer_cal[0], 10);
		cout << answer_cal[0] << endl;
	}
	else
	{
		if (ans[2] != 1)
		{
			if (ans[0] == 0)  //�ٷ���
			{
				_itoa(ans[1], answer_cal[2], 10);
				_itoa(ans[2], answer_cal[3], 10);

				strcat(answer_cal[2], answer_cal[5]);
				strcat(answer_cal[2], answer_cal[3]);
				strcpy(answer_cal[0], answer_cal[2]);
				cout << answer_cal[0] << endl;
			}
			else    //�����
			{
				_itoa(ans[0], answer_cal[1], 10);
				_itoa(ans[1], answer_cal[2], 10);
				_itoa(ans[2], answer_cal[3], 10);

				strcat(answer_cal[2], answer_cal[5]);
				strcat(answer_cal[2], answer_cal[3]);
				strcat(answer_cal[1], answer_cal[4]);
				strcat(answer_cal[1], answer_cal[2]);
				strcpy(answer_cal[0], answer_cal[1]);
				cout << answer_cal[0] << endl;
			}
		}
		else //��Ȼ��
		{
			_itoa(ans[1], answer_cal[2], 10);
			strcpy(answer_cal[0], answer_cal[2]);
			cout << answer_cal[0] << endl;
		}
	}
}