#include "KoreanStudent.h"

bool KoreanStudent::ScoreCheck()
{
	KoreanScore* koreanScore = dynamic_cast<KoreanScore*>(GetScore());

	if (koreanScore == NULL)
		return false;

	cout << endl << "== ���� ���� �л� ���� ==" << endl;
	koreanScore->DrawScore();

	return true;
}