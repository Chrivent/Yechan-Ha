#include "MathStudent.h"

bool MathStudent::ScoreCheck()
{
	MathScore* mathScore = dynamic_cast<MathScore*>(GetScore());

	if (mathScore == NULL)
		return false;

	cout << endl << "== 수학 전공 학생 점수 ==" << endl;
	mathScore->DrawScore();

	return true;
}