#include "KoreanScore.h"

KoreanScore::KoreanScore()
{
	cout << "국어 점수 입력 : ";
	cin >> score;
}

void KoreanScore::DrawScore()
{
	cout << "국어 점수 : " << score << "점" << endl;
}