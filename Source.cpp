#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int qNO;	//�O��̖�萔
int QNO;	//����̖�萔


int get_data(void)	//�O��̋L�^��ǂݎ��
{
	FILE *fpr;
	int best, level;

	fpr = fopen("SCORE.txt", "r");
	if (fpr == NULL)
	{
		printf("����Ȃ̂ŃX�R�A�t�@�C����V�K�쐬���܂��B\n");
		best = 0;
	}
	else
	{
		int year, month, day, h, m, s;
		fscanf(fpr, "%d%d%d%d%d%d", &year, &month, &day, &h, &m, &s);
		fscanf(fpr, "%d%d", &best, &qNO);
		fscanf(fpr, "%d", &level);

		printf("�O��A�ō����_���L�^�����̂�%04d�N%02d��%02d��%02d��%02d��%02d�b�ł����B\n", year, month, day, h, m, s);
		printf("�ō����_��%d�⒆%d��ł����B\n", qNO, best);

		fclose(fpr);

	}

	return (best);
}

void put_data(int best, int QNO)	//����̍X�V
{
	FILE *fps;
	time_t t = time(NULL);
	struct tm *local = localtime(&t);

	if ((fps = fopen("SCORE.txt", "w")) == NULL) {
		printf("ERROR\n");
		exit(-1);
	}

	fprintf(fps, "%d %d %d %d %d %d\n", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	fprintf(fps, "%d %d\n", best, QNO);

	fclose(fps);
}




int difficult(void)
{
	int level, i;
	printf("��Փx��I�����Ă��������B\n1.��2���@2.2���@3.��1��\n");
	scanf("%d", &level);
	if ((level != 1) && (level != 2) && (level != 3))
	{
		for (i = 1; i <= 10; i++)
		{
			printf("��������Փx��I�����Ă��������B\n��2���@2.2���@3.��1��\n\n");
			scanf("%d", &level);
			if ((level == 1) || (level == 2) || (level == 3))
				break;

		}
		if (i = 10)
		{
			printf("��Փx���I������܂���ł����B\n");
			exit(-1);
		}

	}

	return (level);
}

int game(void)	//���͕\���ƃX�R�A�v�Z
{
	int count = 1, score = 0;
	int answer, CorrectAns;
	FILE *fp;
	char str[256];

	if (difficult() == 1)
	{
		fp = fopen("Quasi_Grade2.txt", "r");
		if (fp == NULL)
		{
			exit(-1);
		}
	}

	else if (difficult() == 2)
	{
		fp = fopen("Grade2.txt", "r");
		if (fp == NULL)
		{
			exit(-1);
		}
	}

	else if (difficult() == 3)
	{
		fp = fopen("Quasi_Grade1.txt", "r");
		if (fp == NULL)
		{
			exit(-1);
		}
	}

	else
	{
		printf("ERROR\nFile Not Open\n");
		exit(-1);
	}

	printf("���ꂩ���肪�\������܂��B\n�I�����̐擪�̐�������͂��ĉ������B\n\n");
	printf("Start!!\n");

	while (fgets(str, 256, fp) != NULL)
	{

		if ((count % 3 == 1) || (count % 3 == 2))
		{
			printf("%s\n", str);
		}


		if (count % 3 == 0)
		{
			CorrectAns = atoi(str);
			scanf("%d", &answer);
			if (CorrectAns == answer)
			{
				printf("�����I�I\n\n");
				score++;
				QNO++;
			}
			else
			{
				printf("�c�O�I�I\n������%d�ł��B\n\n", CorrectAns);
				QNO++;
			}
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

	put_data(best, QNO);


	return (0);
}