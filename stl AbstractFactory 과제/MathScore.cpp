#include "MathScore.h"

MathScore::MathScore()
{
	cout << "���� ���� �Է� : ";
	cin >> score;
}

void MathScore::DrawScore()
{
	cout << "���� ���� : " << score << "��" << endl;
}