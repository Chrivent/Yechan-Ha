#pragma once

#include "Part.h"

class WaterTurbine : public Part
{
public:
	WaterTurbine();

	void IncreaseVoltage();
	void Draw(HDC hdc);

	~WaterTurbine();
};