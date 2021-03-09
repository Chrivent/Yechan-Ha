#pragma once

#include "Shell.h"

class TorpedoShell : public Shell
{
public:
	TorpedoShell(Unit* target);

	void Move();
	void Draw(HDC hdc);
};