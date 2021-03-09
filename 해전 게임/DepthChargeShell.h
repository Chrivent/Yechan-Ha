#pragma once

#include "Shell.h"

class DepthChargeShell : public Shell
{
public:
	DepthChargeShell();

	void Move();
	void Draw(HDC hdc);
};