#include "KoreanStudentFactory.h"

Score* KoreanStudentFactory::CreateScore()
{
	return new KoreanScore;
}

Student* KoreanStudentFactory::CreateStudent()
{
	cout << "국어 전공 학생 등록" << endl;

	return new KoreanStudent;
}