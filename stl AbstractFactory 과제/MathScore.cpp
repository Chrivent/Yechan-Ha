#include "MathScore.h"

MathScore::MathScore()
{
	cout << "수학 점수 입력 : ";
	cin >> score;
}

void MathScore::DrawScore()
{
	cout << "수학 점수 : " << score << "점" << endl;
}