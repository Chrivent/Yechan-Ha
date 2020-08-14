#pragma once

#include "StudentFactory.h"
#include "EnglishStudent.h"

class EnglishStudentFactory : public StudentFactory
{
public:
	Score* CreateScore();
	Student* CreateStudent();
};