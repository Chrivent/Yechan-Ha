#pragma once

#include "mecro.h"

class Background : public Object
{
private:
	int type;

public:
	Background();

	void Cheering();
	void Draw(HDC hdc);

	~Background();
};