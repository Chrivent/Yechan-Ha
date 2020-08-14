#pragma once

#include "StudentFactory.h"
#include "MathStudent.h"

class MathStudentFactory : public StudentFactory
{
public:
	Score* CreateScore();
	Student* CreateStudent();
};