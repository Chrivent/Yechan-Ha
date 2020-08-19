#include "EnglishStudentFactory.h"

Score* EnglishStudentFactory::CreateScore()
{
	return new EnglishScore;
}

Student* EnglishStudentFactory::CreateStudent()
{
	cout << "���� ���� �л� ���" << endl;

	return new EnglishStudent;
}