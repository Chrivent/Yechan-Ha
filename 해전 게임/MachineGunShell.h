#pragma once

#include "Shell.h"

class MachineGunShell : public Shell
{
private:
	float angle;
	int moveCount;

public:
	MachineGunShell(float angle, string type);

	void Move();
	void Draw(HDC hdc);
};