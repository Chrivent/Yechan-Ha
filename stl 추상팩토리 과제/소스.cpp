#include "EnglishStudentFactory.h"
#include "KoreanStudentFactory.h"
#include "MathStudentFactory.h"

void DrawScore(Student* student)
{
	if (!student->ScoreCheck())
		cout << "잘못된 점수 배정입니다." << endl;
}

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	EnglishStudentFactory* englishStudentFactory = new EnglishStudentFactory;
	KoreanStudentFactory* koreanStudentFactory = new KoreanStudentFactory;
	MathStudentFactory* mathStudentFactory = new MathStudentFactory;

	Student* eng_student = englishStudentFactory->CreateStudent();
	Student* kor_student = koreanStudentFactory->CreateStudent();
	Student* math_student = mathStudentFactory->CreateStudent();

	Score* eng_score = englishStudentFactory->CreateScore();
	Score* kor_score = koreanStudentFactory->CreateScore();
	Score* math_score = mathStudentFactory->CreateScore();

	eng_student->SetScore(eng_score);
	kor_student->SetScore(kor_score);
	math_student->SetScore(math_score);

	DrawScore(eng_student);
	DrawScore(kor_student);
	DrawScore(math_student);
}