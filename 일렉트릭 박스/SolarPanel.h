#pragma once

#include "Part.h"

class SolarPanel : public Part
{
public:
	SolarPanel();

	void IncreaseVoltage();
	void Draw(HDC hdc);

	~SolarPanel();
};