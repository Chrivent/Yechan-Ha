#pragma once

#include "mecro.h"

class Score
{
protected:
	int score;

public:
	virtual void DrawScore() = 0;
};