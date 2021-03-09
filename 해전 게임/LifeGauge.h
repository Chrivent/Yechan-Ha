#pragma once

#include "mecro.h"

class LifeGauge : public Object
{
private:
	int lifeMax;
	int life;

public:
	LifeGauge(int life);

	void DecreaseLife(int damage);
	bool CheckLifeIsExhausted();
	void Draw(HDC hdc);
};