#include "KoreanStudent.h"

bool KoreanStudent::ScoreCheck()
{
	KoreanScore* koreanScore = dynamic_cast<KoreanScore*>(GetScore());

	if (koreanScore == NULL)
		return false;

	cout << endl << "== 국어 전공 학생 점수 ==" << endl;
	koreanScore->DrawScore();

	return true;
}