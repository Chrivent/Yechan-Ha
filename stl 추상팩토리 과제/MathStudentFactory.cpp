#include "MathStudentFactory.h"

Score* MathStudentFactory::CreateScore()
{
	return new MathScore;
}

Student* MathStudentFactory::CreateStudent()
{
	cout << "���� ���� �л� ���" << endl;

	return new MathStudent;
}