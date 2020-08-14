#pragma once

#include "StudentFactory.h"
#include "KoreanStudent.h"

class KoreanStudentFactory : public StudentFactory
{
public:
	Score* CreateScore();
	Student* CreateStudent();
};