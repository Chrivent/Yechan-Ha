#include "EnglishScore.h"

EnglishScore::EnglishScore()
{
	cout << "���� ���� �Է� : ";
	cin >> score;
}

void EnglishScore::DrawScore()
{
	cout << "���� ���� : " << score << "��" << endl;
}