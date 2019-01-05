#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int qNO;	//�O��̖�萔
int QNO;	//����̖�萔


int get_data(void)	//�O��̋L�^��ǂݎ��
{
	FILE *fp;
	int best;

	if ((fp = fopen("SCORE.txt", "r")) == NULL)
	{
		printf("����Ȃ̂ŃX�R�A�t�@�C����V�K�쐬���܂��B\n");
		best = 0;
	}
	else
	{
		int year, month, day, hour, minute, second;
		fscanf(fp, "%d%d%d%d%d%d", &year, &month, &day ,&hour, &minute, &second);
		fscanf(fp, "%d%d", &best, &qNO);

		printf("�O��̍ō����_��\n%04d�N%02d��%02d��%02d��%02d��%02d�b��\n", year, month, day, hour, minute, second);
		printf("%d�⒆%d��ł����B", qNO, best);

		fclose(fp);
	}

	return (best);
}

void put_data(int best)	//����̎��ԍX�V
{
	FILE *fp;
	time_t t = time(NULL);
	struct tm *local = localtime(&t);

	fp = fopen("SCOR.txt", "w");

	fprintf(fp,"%d%d%d%d%d%d\n",local-> tm_year + 1900, local->tm_mon + 1,
				local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	fprintf(fp, "%d %d\n", best, QNO);

	fclose(fp);
}

int game(void)	//���͕\���ƃX�R�A�v�Z
{
	int count = 0, Linecount = 1,score=0;
	int anser, CorrectAns;
	FILE *fp;
	char str[256];

	printf("��Փx��I�����Ă��������B\n1.��2���@2.2���@3.��1��");

	printf("���ꂩ���肪�\������܂��B\n�I�����̐擪�̐�������͂��ĉ������B\n\n");
	printf("Start!!\n");

	if ((fp = fopen("Quiz.txt", "r")) == NULL)
	{
		printf("file not open !\n");
		return -1;
	}

	while (fgets(str, 256, fp) != NULL)
	{

		if (count % 3 == 0)
		{
			CorrectAns = atoi(str);
			scanf("%d", &anser);
			if (CorrectAns == anser)
			{
				printf("�����I�I\n");
				count++;
				score++;
			}
			else
			{
				printf("�c�O�I�I");
				printf("%s", str);
			}
		}

		else
		{
			printf("%s\n", str);
		}

		count++;
	}

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