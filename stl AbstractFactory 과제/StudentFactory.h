#pragma once

#include "Student.h"

class StudentFactory
{
protected:
	Student* student;
	Score* score;

public:
	virtual Score* CreateScore() = 0;
	virtual Student* CreateStudent() = 0;
};