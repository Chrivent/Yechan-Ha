#pragma once

#include "mecro.h"

class Background
{
private:
	int type;
	bool cheer;

public:
	Background();

	void PassingBackward();
	void PassingForward();
	void Cheering();
	void Draw(HDC hdc);

	~Background();
};