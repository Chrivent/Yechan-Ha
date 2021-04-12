#pragma once

#include "Part.h"

class LightBulb : public Part
{
public:
	LightBulb();

	void IncreaseVoltage();
	void Draw(HDC hdc);

	~LightBulb();
};