#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int qNO;	//�O��̖�萔
int QNO;	//����̖�萔


int get_data(void)	//�O��̋L�^��ǂݎ��
{
	FILE *fpr;
	int best;
	fpr = fopen("SCORE.txt", "r");
	if (fpr == NULL)
	{
		printf("����Ȃ̂ŃX�R�A�t�@�C����V�K�쐬���܂��B\n");
		best = 0;
	}
	else
	{
		int year, month, day, hour, minute, second;
		fscanf(fpr, "%d%d%d%d%d%d", &year, &month, &day ,&hour, &minute, &second);
		fscanf(fpr, "%d%d", &best, &qNO);

		printf("�O��̍ō����_��\n%04d�N%02d��%02d��%02d��%02d��%02d�b��\n", year, month, day, hour, minute, second);
		printf("%d�⒆%d��ł����B", qNO, best);

		fclose(fpr);
	}

	return (best);
}

void put_data(int best)	//����̎��ԍX�V
{
	FILE *fps;
	time_t t = time(NULL);
	struct tm *local = localtime(&t);

	fps = fopen("SCOR.txt", "w");

	fprintf(fps,"%d%d%d%d%d%d\n",local-> tm_year + 1900, local->tm_mon + 1,
				local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	fprintf(fps, "%d %d\n", best, QNO);

	fclose(fps);
}

int game(void)	//���͕\���ƃX�R�A�v�Z
{
	int count = 0, Linecount = 1,score=0;
	int answer, CorrectAns,level,i;
	FILE *fp;
	char str[256];

	printf("��Փx��I�����Ă��������B\n1.��2���@2.2���@3.��1��\n");
	scanf("%d", &level);
	if ((level != 1) && (level != 2) && (level != 3))
	{
		for (i = 1; i <= 10; i++)
		{
			printf("��������Փx��I�����Ă��������B\n��2���@2.2���@3.��1��");
			scanf("%d", &level);
			if ((level == 1) || (level == 2) || (level == 3))
				break;
			
		}
		if (i = 10)
		{
			printf("��Փx���I������܂���ł����B");
			exit(-1);
		}

	}
	printf("���ꂩ���肪�\������܂��B\n�I�����̐擪�̐�������͂��ĉ������B\n\n");
	printf("Start!!\n");

	if (level == 1)
	{
		fp = fopen("Quasi_Grade2", "r");
		if (fp==NULL)
		{
			exit(-1);
		}
	}

	else if (level == 2)
	{
		fp = fopen("Grade2", "r");
		if (fp == NULL)
		{
			exit(-1);
		}
	}

	else if (level == 3)
	{
		fp = fopen("Quasi_Grade1", "r");
		if (fp == NULL)
		{
			exit(-1);
		}
	}

	else
	{
		printf("ERROR\nFile Not Open");
		exit(-1);
	}

	while (fgets(str, 256, fp) != NULL)
	{

		if (count % 3 == 0)
		{
			CorrectAns = atoi(str);
			scanf("%d", &answer);
			if (CorrectAns == answer)
			{
				printf("�����I�I\n");
				count++;
				score++;
				QNO++;
			}
			else
			{
				printf("�c�O�I�I");
				printf("%s", str);
				QNO++;
			}
		}

		else
		{
			printf("%s\n", str);
		}

		count++;
	}
	fclose(fp);
	return(score);

}

void result(int best, int score)
{
	printf("\n���Ȃ���%d�⒆%d�␳���ł���!\n", QNO, score);
	printf("�O���%d�⒆%d�␳���ł����B\n", qNO, best);
}

int main(void)
{
	int score;
	int best;

	best = get_data();

	score = game();
	result(best, score);

	if (score > best) {
		printf("�ō����_���X�V���܂���!!\n");
		best = score;
	}

	put_data(best);

	return (0);
}