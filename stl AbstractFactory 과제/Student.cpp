#include "Student.h"

void Student::SetScore(Score* score)
{
	this->score = score;
}

Score* Student::GetScore()
{
	return score;
}