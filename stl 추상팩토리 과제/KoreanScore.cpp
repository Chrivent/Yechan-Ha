#include "KoreanScore.h"

KoreanScore::KoreanScore()
{
	cout << "���� ���� �Է� : ";
	cin >> score;
}

void KoreanScore::DrawScore()
{
	cout << "���� ���� : " << score << "��" << endl;
}