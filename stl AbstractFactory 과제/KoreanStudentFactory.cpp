#include "KoreanStudentFactory.h"

Score* KoreanStudentFactory::CreateScore()
{
	return new KoreanScore;
}

Student* KoreanStudentFactory::CreateStudent()
{
	cout << "���� ���� �л� ���" << endl;

	return new KoreanStudent;
}