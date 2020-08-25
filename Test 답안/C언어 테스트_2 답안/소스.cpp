#include<stdio.h>
#include<Windows.h>

void Quiz1(int num1, int num2)
{
	int bigNum = (num1 > num2) ? num1 : num2;

	if (bigNum % 2 == 0)
		printf("ū ���̸鼭 ¦�� : %d\n", bigNum);
}

void Quiz2(int koreanScore, int englishScore, int mathScore)
{
	int sumScore = koreanScore + englishScore + mathScore;
	float averageScore = (float)sumScore / 3.0f;

	char rank;
	if (averageScore >= 90)
		rank = 'A';
	else if (averageScore >= 80)
		rank = 'B';
	else if (averageScore >= 70)
		rank = 'C';
	else if (averageScore >= 60)
		rank = 'D';
	else
		rank = 'F';

	printf("�հ� ���� : %d\n", sumScore);
	printf("��� ���� : %.2f\n", averageScore);
	printf("��� : %c\n", rank);
}

void Quiz3()
{
	int sum = 0;
	for (int i = 1; i <= 1000; i++)
	{
		if (i % 3 == 0)
		{
			if (i % 5 != 0)
				continue;
		}

		sum += i;
	}
	printf("3�� ����� ������ 1 ~ 1000������ ��(3�� 5�� ������� ����) : %d\n", sum);
}

void Quiz4()
{
	int sum = 0;

	while (true)
	{
		int input;
		printf("�Է� : ");
		scanf("%d", &input);

		if (input != 0)
			sum += input;
		else
		{
			printf("�Է��� ���� �� : %d\n", sum);
			return;
		}
	}
}

void Quiz5()
{
	int num = rand() % 100;

	while (true)
	{
		int input;
		printf("�Է� : ");
		scanf("%d", &input);

		if (input > num)
			printf("%d ���� ���� �� �Դϴ�.\n", input);
		else if (input < num)
			printf("%d ���� ū �� �Դϴ�.\n", input);
		else if (input == num)
		{
			printf("����\n");
			return;
		}
	}
}

void main()
{
	printf("1.\n");
	Quiz1(12, 15);
	printf("\n");

	printf("2.\n");
	Quiz2(85, 90, 95);
	printf("\n");

	printf("3.\n");
	Quiz3();
	printf("\n");

	printf("4.\n");
	Quiz4();
	printf("\n");

	printf("5.\n");
	Quiz5();
	printf("\n");

	system("pause");
}