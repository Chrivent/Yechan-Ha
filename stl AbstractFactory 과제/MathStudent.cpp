#include "MathStudent.h"

bool MathStudent::ScoreCheck()
{
	MathScore* mathScore = dynamic_cast<MathScore*>(GetScore());

	if (mathScore == NULL)
		return false;

	cout << endl << "== ���� ���� �л� ���� ==" << endl;
	mathScore->DrawScore();

	return true;
}