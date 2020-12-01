#pragma once

#include "Background.h"

class Ring : public Object
{
private:
	int type;

public:
	Ring();

	void Flaming();
	void FastMove();
	void SlowMove();
	void SlowestMove();
	void Draw(HDC hdc);
	void Draw2(HDC hdc);

	~Ring();
};