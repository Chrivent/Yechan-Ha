#pragma once

#include "Score.h"

class Student
{
protected:
	Score* score;

public:
	void SetScore(Score* score);
	Score* GetScore();

	virtual bool ScoreCheck() = 0;
};