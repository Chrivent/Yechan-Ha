#include "EnglishStudent.h"

bool EnglishStudent::ScoreCheck()
{
	EnglishScore* englishScore = dynamic_cast<EnglishScore*>(GetScore());

	if (englishScore == NULL)
		return false;

	cout << endl << "== ���� ���� �л� ���� ==" << endl;
	englishScore->DrawScore();

	return true;
}