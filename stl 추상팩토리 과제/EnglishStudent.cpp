#include "EnglishStudent.h"

bool EnglishStudent::ScoreCheck()
{
	EnglishScore* englishScore = dynamic_cast<EnglishScore*>(GetScore());

	if (englishScore == NULL)
		return false;

	cout << endl << "== 영어 전공 학생 점수 ==" << endl;
	englishScore->DrawScore();

	return true;
}