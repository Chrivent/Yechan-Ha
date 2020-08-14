#include "EnglishScore.h"

EnglishScore::EnglishScore()
{
	cout << "영어 점수 입력 : ";
	cin >> score;
}

void EnglishScore::DrawScore()
{
	cout << "영어 점수 : " << score << "점" << endl;
}