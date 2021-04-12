#pragma once

#include "Part.h"

class WaterDispenser : public Part
{
public:
	WaterDispenser();

	void IncreaseVoltage();
	void Draw(HDC hdc);

	~WaterDispenser();
};