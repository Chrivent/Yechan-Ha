#include "MathStudentFactory.h"

Score* MathStudentFactory::CreateScore()
{
	return new MathScore;
}

Student* MathStudentFactory::CreateStudent()
{
	cout << "수학 전공 학생 등록" << endl;

	return new MathStudent;
}