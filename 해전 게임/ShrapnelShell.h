#pragma once

#include "Shell.h"

class ShrapnelShell : public Shell
{
private:
	Position targetPosition;
	float angle;
	float angle2;
	bool explode;
	int moveCount;

public:
	ShrapnelShell(Position targetPosition, float angle, float angle2);

	void Move();
	void Draw(HDC hdc);
};