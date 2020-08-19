#include "EnglishStudentFactory.h"

Score* EnglishStudentFactory::CreateScore()
{
	return new EnglishScore;
}

Student* EnglishStudentFactory::CreateStudent()
{
	cout << "영어 전공 학생 등록" << endl;

	return new EnglishStudent;
}