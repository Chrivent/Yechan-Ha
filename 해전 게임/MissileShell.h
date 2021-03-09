#pragma once

#include "Shell.h"

class MissileShell : public Shell
{
private:
	int mode;
	int moveCount;

public:
	MissileShell(Unit* target);

	void Move();
	void Draw(HDC hdc);
};